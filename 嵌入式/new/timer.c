#include "stdio.h"
#define GPKCON0             (*((volatile unsigned long *)0x7F008800))
#define GPKDATA                 (*((volatile unsigned long *)0x7F008808))
#define GPKDAT              (*((volatile unsigned long *)0x7F008808))
#define EINT0CON0           (*((volatile unsigned long *)0x7F008900))
#define EINT0MASK           (*((volatile unsigned long *)0x7F008920))
#define EINT0PEND           (*((volatile unsigned long *)0x7F008924))
#define PRIORITY            (*((volatile unsigned long *)0x7F008280))
#define SERVICE             (*((volatile unsigned long *)0x7F008284))
#define SERVICEPEND         (*((volatile unsigned long *)0x7F008288))
#define VIC0IRQSTATUS       (*((volatile unsigned long *)0x71200000))
#define VIC0FIQSTATUS       (*((volatile unsigned long *)0x71200004))
#define VIC0RAWINTR         (*((volatile unsigned long *)0x71200008))
#define VIC0INTSELECT       (*((volatile unsigned long *)0x7120000c))
#define VIC0INTENABLE       (*((volatile unsigned long *)0x71200010))
#define VIC0INTENCLEAR      (*((volatile unsigned long *)0x71200014))
#define VIC0PROTECTION      (*((volatile unsigned long *)0x71200020))
#define VIC0SWPRIORITYMASK  (*((volatile unsigned long *)0x71200024))
#define VIC0PRIORITYDAISY   (*((volatile unsigned long *)0x71200028))
#define VIC0ADDRESS         (*((volatile unsigned long *)0x71200f00))

#define     PWMTIMER_BASE           (0x7F006000)
#define     TCFG0       ( *((volatile unsigned long *)(PWMTIMER_BASE+0x00)) )
#define     TCFG1       ( *((volatile unsigned long *)(PWMTIMER_BASE+0x04)) )
#define     TCON        ( *((volatile unsigned long *)(PWMTIMER_BASE+0x08)) )
#define     TCNTB0      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x0C)) )
#define     TCMPB0      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x10)) )
#define     TCNTO0      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x14)) )
#define     TCNTB1      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x18)) )
#define     TCMPB1      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x1C)) )
#define     TCNTO1      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x20)) )
#define     TCNTB2      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x24)) )
#define     TCMPB2      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x28)) )
#define     TCNTO2      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x2C)) )
#define     TCNTB3      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x30)) )
#define     TCMPB3      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x34)) )
#define     TCNTO3      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x38)) )
#define     TCNTB4      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x3C)) )
#define     TCNTO4      ( *((volatile unsigned long *)(PWMTIMER_BASE+0x40)) )
#define     TINT_CSTAT  ( *((volatile unsigned long *)(PWMTIMER_BASE+0x44)) )

#define GPFCON (*(volatile unsigned int *)0x7F0080A0)
#define GPFDAT (*(volatile unsigned int *)0x7F0080A4)
typedef void (isr)(void);
extern void asm_timer_irq();
extern int COUNT;
int mode;
int count;
int interval;
void irq_init(void)
{
    /* 在中断控制器里使能timer0中断 */
    VIC0INTENABLE |= (1 << 23);

    VIC0INTSELECT = 0;

    isr** isr_array = (isr**)(0x7120015C);

    isr_array[0] = (isr*)asm_timer_irq;

    /*将GPK4-GPK7配置为输出口*/
    GPKCON0 = 0x11110000;

    //熄灭四个LED灯
    GPKDATA = 0xff;

    // set GPF14 as output
    GPFCON |= 1 << 28;
    GPFCON &= ~(1 << 29);
}
// timer0中断的中断处理函数
void do_irq()
{
    // K1对应的操作
    if (mode == 0)
    {
        if(count != 0){
            GPFDAT ^= 0x00004000;//设置蜂鸣器按规定间隔时间持续鸣叫
            if(GPFDAT & 1 << 14){//蜂鸣器每响一次，count-1
                count --;
            }
        }
    }
    // K2对应的操作
    if (mode == 1)
    {
		if(interval == 0)
			GPFDAT = 0x00004000;
		else if(interval == 1)
			GPFDAT = 0x00004000;
		else if(interval == 3)
			GPFDAT = 0x00004000;
		else if(interval == 4)
			GPFDAT = 0x00004000;
		else if(interval == 6)
			GPFDAT = 0x00004000;
		else if(interval == 2 || interval == 5 || interval ==7)
			GPFDAT = 0x00000000;
		if(interval >= 7)
			interval = -1;
        interval ++;
    }
    // K3对应的操作
    if (mode == 2)
    {
		if(interval == 0)
			GPFDAT = 0x00004000;
		else if(interval == 2)
			GPFDAT = 0x00004000;
		else if(interval == 4)
			GPFDAT = 0x00004000;
		else if(interval == 5)
			GPFDAT = 0x00004000;
		else if(interval == 1 || interval == 3 || interval == 6)
			GPFDAT = 0x000000f0;
		else if(interval >= 6)
			interval = -1;
        interval++;
    }
    unsigned long uTmp;
    //清timer0的中断状态寄存器
    uTmp = TINT_CSTAT;
    TINT_CSTAT = uTmp;
    VIC0ADDRESS = 0x0;
}

// 初始化timer
void timer_init(unsigned long utimer, unsigned long uprescaler, unsigned long udivider, unsigned long utcntb, unsigned long utcmpb, int mode_x, int countk)
{
    unsigned long temp0;
    // 设置mode值，用于判断执行哪一种操作
    mode = mode_x;
    count = countk;//KEY1按下的次数
    interval = 0;
    // 定时器的输入时钟 = PCLK / ( {prescaler value + 1} ) / {divider value} = PCLK/(65+1)/16=62500hz

    //设置预分频系数为66
    temp0 = TCFG0;
    temp0 = (temp0 & (~(0xff00ff))) | (uprescaler << 0);
    TCFG0 = temp0;

    // 16分频
    temp0 = TCFG1;
    temp0 = (temp0 & (~(0xf << 4 * utimer)) & (~(1 << 20))) | (udivider << 4 * utimer);
    TCFG1 = temp0;

    // 1s = 62500hz
    TCNTB0 = utcntb;
    TCMPB0 = utcmpb;

    // 手动更新
    TCON |= 1 << 1;

    // 清手动更新位
    TCON &= ~(1 << 1);

    // 自动加载和启动timer0
    TCON |= (1 << 0) | (1 << 3);

    // 使能timer0中断
    temp0 = TINT_CSTAT;
    temp0 = (temp0 & (~(1 << utimer))) | (1 << (utimer));
    TINT_CSTAT = temp0;
}



