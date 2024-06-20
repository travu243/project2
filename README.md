# Control 4 omni 
project sử dụng stm32f4 discovery

* file control4omniX.h
file thư viện sử dụng cho stm32f103c8

# Cách sử dụng

hàm Da_huong_4banh() có 5 tham số:

Huong_tinh_tien: hướng di chuyển của robot
Huong_xoay: hướng của robot
Toc_doxoay: tốc độ xoay của robot nếu robot có xoay
SPEED_tinhtien: tốc độ di chuyển của robot
Enable_rotate_one_spot: cho phép quay tại chỗ


vi du:

Da_huong_4banh(0,90,10,60,0);

Huong_tinh_tien=0;
Huong_xoay=90;
Toc_doxoay=10;				(càng tăng càng chậm)
SPEED_tinhtien=60;			(max: SPEED_LIMIT)
Enable_rotate_one_spot=0;	(ko cho phép quay tại chỗ)


* Bước 1: include control4omnix.h
* Bước 2: viết vào hàm main()
  MotorA.K = 30;
	MotorB.K = 30;
	MotorC.K = 30;
	MotorD.K = 30;

	MotorA.Offset = 0;
	MotorB.Offset = 0;
	MotorC.Offset = 0;
	MotorD.Offset = 0;
* Bước 3: extern các biến sang file stm32f1xx_it.c để tính toán cập nhật tốc độ và hướng các bánh xe

extern int16_t SPEED;
extern int16_t SPEED_mong_muon;
extern int16_t xoay;
extern volatile int16_t Beta;
extern uint8_t Value_vantoc_goc;
extern uint8_t Value_Giatoc;


extern uint8_t giatoc_giamtoc;
extern uint8_t dahuong_exit;
extern uint16_t value_game;


extern float Huong_tinh_tien;
extern volatile int16_t Huong_xoay;
extern volatile int16_t Toc_doxoay;
extern volatile int16_t SPEED_tinhtien;
extern __IO uint8_t Value_giatoc_pwm;

extern uint8_t Enable_rotate_one_spot;
extern uint8_t Lock_Whell;

extern uint8_t Giatoc_tinh_tien;

extern void Da_huong_4banh(float Huong_tinh_tien_alpha, volatile int16_t beta , uint8_t value_locity, uint8_t SPEED_TINH_TIEN,uint8_t XOAY_TAI_CHO);

uint8_t num=0;

void Tang_giam_SPEED(void)
{
	static uint8_t i;
	static uint8_t j,k;

	if(SPEED != SPEED_mong_muon){
		if(++i > Giatoc_tinh_tien){
			i=0;
			if(SPEED > SPEED_mong_muon) {
				SPEED--;
				if(SPEED <= SPEED_mong_muon) SPEED = SPEED_mong_muon;
			}
			else{
				SPEED++;
				if(SPEED >= SPEED_mong_muon )SPEED = SPEED_mong_muon;
			}
		}
	}
	if(xoay != Beta){
		if(++j > Value_vantoc_goc){
			j=0;
			if(xoay < 0){
				Beta--;
				if(Beta <= xoay) Beta = xoay;
			}
			else{
				Beta++;
				if(Beta >= xoay) Beta = xoay;
			}
		}
	}
	if(xoay == 0 && Beta != 0){
		if(++k > Value_vantoc_goc){
			k=0;
			if(Beta < 0){
				Beta++;
				if(Beta >= 0) Beta = xoay;
			}
			else if(Beta > 0){
				Beta--;
				if(Beta <= 0) Beta = xoay;
			}
		}
	}
}

* Bước 4: cho vào 1 timer interrupt mỗi 1ms để update

	if(Lock_Whell == 1){
		Da_huong_4banh(Huong_tinh_tien, Huong_xoay, Toc_doxoay, SPEED_tinhtien,Enable_rotate_one_spot);
	}
	Tang_giam_SPEED();

* Bước 5: uart dma la bàn và gán vào biến value_compass (value_compass=(data[0]<<8|data[1]))



