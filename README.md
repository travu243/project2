# Control 4 omni 
project sử dụng stm32f4 discovery

* file control4omniX.h
file thư viện sử dụng cho stm32f103c8

# Cách sử dụng

ham` Da_huong_4banh() co' 5 tham so':

Huong_tinh_tien: huong' di chuyen? cua? robot
Huong_xoay: huong' mat. cua? robot
Toc_doxoay: toc' do. xoay cua? robot neu' robot co' xoay
SPEED_tinhtien: toc' do. di chuyen' cua? robot
Enable_rotate_one_spot: cho phep' quay tai. cho~ (bat. cai' nay` thi` ko di chuyen? dc, chi? dung' im fix goc')


vi du:

Da_huong_4banh(0,90,10,60,0);

Huong_tinh_tien=0;
Huong_xoay=90;
Toc_doxoay=10;				(cang` tang cang` cham.)
SPEED_tinhtien=60;			(max: SPEED_LIMIT)
Enable_rotate_one_spot=0;	(ko cho phep' xoay tai. cho~)

![image](https://hackmd.io/_uploads/S10zUVZI0.png)

