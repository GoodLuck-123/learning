[TOC]

## some useful notes

### conda安装ros1与ros2环境







### 配置FAST_LIVO2

安装conda社区稳定的ros1自带pcl和eigen，故仅Sophus需要手动编译源码，用此仓库内的Sophus（版本为a621ff）且做了源码修改以通过编译
```bash
cd Sophus
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
make -j10
make install
```
`注意别用sudo权限，因为miniconda虚拟环境不在root权限的目录里`


### 备份conda环境

```bash
# 备份环境配置
conda env export > ros2_env.yml
# 恢复环境配置，记得改yml文件中最后一行的电脑目录
conda env create -f ros1_env.yml
```

### cmake指定安装到虚拟环境里

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/home/wu/miniconda3/envs/ros2
# 或者
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
```

### 升级了conda或者一些别的操作有以下openssl报错

```bash
# conda 的 OpenSSL 版本错乱 了，尤其是当你安装了 Python 3.13（conda base 环境）之后，而旧环境（ros2, ros1）里
# 依赖的是 Python 3.11 与不同版本的 OpenSSL 库
(base) wu@wu-ZHENGJIUZHE-REN9000-34IMZ:~$ conda activate ros2
(ros2) wu@wu-ZHENGJIUZHE-REN9000-34IMZ:~$ conda deactivate
Error while loading conda entry point: conda-content-trust (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
Error while loading conda entry point: anaconda-auth (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
(base) wu@wu-ZHENGJIUZHE-REN9000-34IMZ:~$ conda activate ros1
Error while loading conda entry point: conda-content-trust (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
Error while loading conda entry point: anaconda-auth (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
(ros1) wu@wu-ZHENGJIUZHE-REN9000-34IMZ:~$ conda deactivate
Error while loading conda entry point: conda-content-trust (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
Error while loading conda entry point: anaconda-auth (/home/wu/miniconda3/lib/python3.13/lib-dynload/../../libssl.so.3: version `OPENSSL_3.2.0' not found (required by /home/wu/miniconda3/envs/ros2/lib/python3.11/site-packages/cryptography/hazmat/bindings/_rust.abi3.so))
```

以下处理命令

```bash
conda deactivate # 退出所有虚拟环境
conda install -n base "openssl>=3.2.0" "cryptography>=42"
source ~/miniconda3/etc/profile.d/conda.sh
```

