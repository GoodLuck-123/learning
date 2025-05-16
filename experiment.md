# 制作先验图
## 修改参数使loop为录制先验图模式
1.在实验板卡本地config文件中修改`load_previous_pose_graph`为0即可进行先验图的录制
> `vim os_project/vins_fusion/config/our_config.yaml`

2.制作先验图
*bag2gps.py*文件中改包名并运行
*chazhi.py*中的*GPS.csv*改成新生成的*包命_gps.csv* *pose_graph*中最后的*xxx.txt*改成*xxx.csv*并运行

3.离线跑可以选择数据包的开始时间
> `rosbag play xxx.bag -s 140`
从140开始

# 无人机正式起飞录数据
## 修改参数使loop为加载先验图进行回环
1.同上修改本地config文件`load_previous_pose_graph`为1
2.开loop_fusion节点加载pose_graph
> `cd sh_files/p600`
>
> `bash loop.sh`

3.开imu与相机驱动
> `bash imu_mavros_cam.bash`

4.起飞悬停一段时间
> 或者是跑本地已有的数据包 无需开驱动 只需先初始化vins算法 直接跑包
> `rosbag play datapackage`

5.开vins算法
> `bash vins.sh`

## 查看数据命令
> `rqt_image_view`
> `rostopic echo /mavros/imu/data`
> `rostopic echo /mavros/global_position/raw/fix`


# 日志
## 20250515
### 硬盘未挂载

### 先是内参重新标，后是尺度有问题，数据经常乱跑 换板卡

### 因分辨率约为原来的两倍而算力不足 vins计算时间加倍

## 20250516
### 换一个板卡 硬盘挂上了，没权限
> `sudo chmod 777 disk`

### 数据没有经常乱跑了，尺度有一点问题