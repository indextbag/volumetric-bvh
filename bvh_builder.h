//--------------------------------------------------------------------------------
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met :
//
//	*Redistributions of source code must retain the above copyright notice, this
//	list of conditions and the following disclaimer.
//
//	* Redistributions in binary form must reproduce the above copyright notice,
//	this list of conditions and the following disclaimer in the documentation
//	and/or other materials provided with the distribution.
//	
//	* Neither the name of the copyright holder nor the names of its
//	contributors may be used to endorse or promote products derived from
//	this software without specific prior written permission.
//	
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//	DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//	OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Copyright(c) 2019, Sergen Eren
// All rights reserved.
//----------------------------------------------------------------------------------
// 
//	Version 1.0: Sergen Eren, 25/10/2019
//
// File: This is the header file for bvh_builder class that takes a vector of 
//		 gpu_vdb volumes and creates an accompanying bvh to be sent to render kernel
//
//-----------------------------------------------




#ifndef _BVH_BUILDER_H_
#define _BVH_BUILDER_H_

#include <cuda.h>
#include <vector>

#include "bvh.h"
#include "gpu_vdb.h"


enum bvh_error_t {

	BVH_INIT_ERR,
	BVH_INIT_FUNC_ERR,
	BVH_LAUNCH_ERR,
	BVH_NO_ERR
};


class BVH_Builder {

private:

#define BLOCK_SIZE 128


private:
	bvh_error_t init_functions(CUmodule &bvh_module);

public:
	BVH_Builder() {};
	~BVH_Builder() {};

	bvh_error_t init();
	bvh_error_t build_bvh(std::vector<GPU_VDB> volumes);

	BVH bvh;

	bool m_debug_bvh = false;

private:

	CUmodule bvh_module;
	CUfunction debug_bvh_func;
	CUfunction build_radix_tree_func;
	CUfunction comp_morton_codes_func;
	CUfunction comp_bbox_func;
	CUfunction construct_bvh_func;

};

#endif // !_BVH_BUILDER_H_
