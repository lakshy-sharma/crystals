# Setting up PyTorch for AMD GPUs.

Recently I found myself setting up my workstation to learn PyTorch. There is abundance of guides on how to setup Nvidia GPUs on Linux for CUDA but similar guides cannot be found for setting up ROCM to work with AMD GPUs. Since I wouldn't buy a brand new GPU to learn AI/ML I though why not fix this problem once and for all.

AMD GPUs do not support Nvidia's development toolkit called CUDA. They have their own platform named ROCM which is being developed rapidly by AMD to catch up with Nvidia.

PyTorch is an open source ML platform which supports both CUDA and ROCM. The only challenge being the ability to setup AMD GPUs for ROCM computations. In this guide I will try to provide a clear pathway for people who are trying to utilize their existing AMD GPUs for machine learning with PyTorch.

I will keep updating this guide as I progress and experiment with more operating systems and ROCM versions.

## Relevant System Specs

All the guides I have provided below have been tested on the following configurations.

1. CPU: AMD Ryzen 5 5600H with Radeon Graphics
2. GPU: AMD Radeon RX 5500M 

## Fedora or RHEL based Systems.

In this section I will describe a setup which allows you to access AMD GPUs on Fedora. The configuration I have tested this guide on is given below: 

* Fedora 40
* PyTorch version 2.4.0
* ROCM version 6.0

### Steps to be followed.

1. Allow non root users to access GPU resources.

    `sudo usermod -a -G video $LOGNAME`

2. Check if your hardware supports rocm. 

    `sudo dnf install rocminfo && rocminfo`
    
    This command should list your available GPU resources. Once the above command works fine and you can locate your GPUs you can proceed with installation of ROCM toolchain.
3. Install OpenCL and HIP modules for ROCM. This module also installs rocm-cliinfo which can be useful in debugging later.

    `sudo dnf install rocm-opencl rocm-hip rocm-clinfo`

    If the HIP module fails the try this command.

    `sudo dnf install rocm-opencl rocm-hip rocm-clinfo - enable-repo=updates-testing`

4. Create a python virtualenv and setup PyTorch.
    
    `python -m venv .isolation && source .isolation/bin/activate`
    
    `pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm6.0`


5. Enter a python shell and test PyTorch.

    `import torch`
    
    `device = torch.device("cuda" if torch.cuda.is_available() else "cpu")`
    
    `print(f"Using device: {device}")`

    If the above command replies back with "cuda" you can safely assume that PyTorch can access your GPU.

    You might have noticed that I made no ROCM based test in PyTorch which indicates that pyTorch has largely the same dev API for both Nvidia and AMD GPUs.

6. **WARNING**: If PyTorch throws errors after starting, you might need to set proper LLVM environment variables.

    1. A sample of such variables is given for the 6900 XT series GPUs. Here the build target is gfx1030 which translates into 10.3.0
        
        `echo “export HSA_OVERRIDE_GFX_VERSION=10.3.0” >> ~/.bashrc && source ~/.bashrc`

    2. Now since not everyone will be using 6900 XT GPU. You must start with recognizing the gfx version of your GPU. You shuld use this command to recognize your gfx version.

        `rocminfo | grep gfx`

        For my GPU the HSA GFX version came gfx1012 which translates to 10.1.2. 

    3. If above command doesnt solve the problem for you then I recommend you refer to this documentation by LLVM: https://llvm.org/docs/AMDGPUUsage.html. This is where I leave you sailor...

    4. As a last resort you can build Pytorch for your achitecture by passing the environment variable before running the build script: PYTORCH_ROCM_ARCH=<arch>

## Debian or Ubuntu Based Systems.

Nowadays Ubuntu is more focussed on bringing shiny new UI changes instead of focussing on its package management and operating system basics. This has lead to a major rot in its package management system where people are often caught off guard by snaps, the awkward security posture that they impose and leading-lagging dependency issues in the development ecosystem. 

For the first time I believe that Debian is becoming more user friendly for programmers compared to Ubuntu.

Currently the best way to manage the amdgpu software on Ubuntu is through amdgpu-install script.

**WARNING**: As of writing this article, amdgpu-install script only manages to install graphics use case on Ubuntu 22.04 and fails to install rocm on Ubuntu 22 LTS, If you any newer versions then it is completely hopeless to even try. 
the best compatibility is on Ubuntu 20.04 (*Yes that last good Ubuntu release*)

### Steps to be followed.

1. Install the AMDGPU install script.
    
    `sudo apt update && wget https://repo.radeon.com/amdgpu-install/6.1/ubuntu/focal/amdgpu-install_6.1.60100-1_all.deb && sudo apt install ./amdgpu-install_6.1.60100-1_all.deb`

2. List the available use cases and go through them once to get a grasp of what this script will be doing.

    `sudo amdgpu-install --list-usecase`

3. Install the rocm use case.

    `sudo amdgpu-install --usecase=rocm`

4. You can now try to setup PyTorch and check whether the GPU is accessible or not. The relevant steps are mentioned in above fedore section from 4 to 6.

4. If this doesnt work. (*Which is very likely*) Uninstalling is as easy as:

    `sudo amdgpu-install --uninstall`


## Conclusion

I hope you have successfully setup your machine to utilize the AMD GPU for learning ML with PyTorch.

*Thank You.*