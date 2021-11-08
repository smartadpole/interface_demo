# lib
set(NPU_LIBRARIES -lOpenVX -lOpenVXU -lArchModelSw -lCLC -lGAL -lNNArchPerf -lVSC -lovxlib)

if (USE_NPU)
    include_directories(/usr/share/npu/sdk/include/)
    set(CNN_LIBRARY ${NPU_LIBRARIES})
elseif(USE_GPU)
    include_directories(${MNN_DIR}/include)
    set(CNN_LIBRARY ${MNN_DIR}/lib/libMNN.so)
endif ()