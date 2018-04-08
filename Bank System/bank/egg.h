/* $Id: egg.h,v 1.4 2005/10/06 12:35:27 sun Exp $  */

/**
 * \mainpage Easy Graphical egG ��Ϸ����ƽ̨
 *
 * \section intro ���
 * Easy Graphical egG (Egg) ��һ������Դ�����C���Ժ����⣬����GPLЭ�顣������
 * ��Ŀ���ǿ���һ������򵥡�ֱ�۵�Win32ƽ̨�µ�ͼ�ζ����⣬C���Եĳ�ѧ�߿���ʹ
 * ����������������Ϸ��ͼ�γ�����C���Ե�ѧϰ���̱�ø���Ȥ�����гɾ͸С�
 * <P>����Egg�����飬����� http://egg.sunner.cn
 * <P>Hosted by http://gf.cs.hit.edu.cn
 */

#ifndef _EGG_SUNNER_HIT     //��ֹ��ΰ���egg.h����ɳ�ͻ
#define _EGG_SUNNER_HIT

#include <windows.h>		//ʹ��Win32 API

struct egg;

//////////////////////////////////////////////////////////////////////////
//
// ������������
//
//////////////////////////////////////////////////////////////////////////

/**
 * \defgroup EggBasic ��������
 * �����������ͺͺ���ʵ����Egg������Ĺ��ܡ�ͨ�����ǿ��Խ���ͼ�δ��ڣ�Eggƽ̨��
 * ��Ϊ���ӣ������������ϻ��Ƽ򵥵�ͼ�κ����֡�
 * @{
 */

/**
 * egg�ľ��
 *
 * @see EggStart(), LayEgg()
 */
typedef struct egg* HEGG;
//! @}

/**
 * \defgroup EggInput ��������
 * �����������ͺͺ���ʵ����Egg��Ӧ�û�����Ĺ��ܡ�ͨ�����ǿ��Եõ��û���������Щ
 * ���̺���갴�������ܵ�֪���ָ���λ�á�
 * @{
 */

/**
 * �¼�����
 *
 * WaitForEvent�ķ���ֵ���ͣ�ͨ�����ж϶�������ʲô���飨�û����롢��ʱ����
 */
typedef enum 
{
    EXIT,           /**< ���˹رմ��ڰ�ť */
    TIMER,          /**< ��ʱ���ڵ� */
    MOUSEMOVE,      /**< ��걻�ƶ� */
    KEYDOWN,        /**< ���̰��������� */
    KEYUP           /**< ���̰������� */
} EVENT_TYPE;

//!@}

//////////////////////////////////////////////////////////////////////////
//
// �����
//
//////////////////////////////////////////////////////////////////////////

/**
 * \defgroup EggAdvGraph �߼�ͼ�ι���
 * ���к�ͺ���ʵ����Egg�ĸ߼�ͼ�ι��ܡ�ͨ�����ǲ������Ի������ߺ�Բ�Σ����ҿ�
 * �Ըı���ɫ���ߴ֡���������ɫ������������λͼ��
 * @{
 */
//!��ɫ
#define BLACK        RGB(0x00, 0x00, 0x00)
//!����ɫ
#define DARK_BLUE    RGB(0x00, 0x00, 0x80)
//!����ɫ
#define DARK_GREEN   RGB(0x00, 0x80, 0x00)
//!����ɫ
#define DARK_CYAN    RGB(0x00, 0x80, 0x80)
//!���ɫ
#define DARK_RED     RGB(0x80, 0x00, 0x00)
//!����ɫ
#define DARK_MAGENTA RGB(0x80, 0x00, 0x80)
//!���ɫ
#define DARK_YELLOW  RGB(0x80, 0x80, 0x00)
//!ǳ��ɫ
#define LIGHT_GRAY   RGB(0xC0, 0xC0, 0xC0)
//!���ɫ
#define DARK_GRAY    RGB(0x80, 0x80, 0x80)
//!��ɫ
#define BLUE         RGB(0x00, 0x00, 0xFF)
//!��ɫ
#define GREEN        RGB(0x00, 0xFF, 0x00)
//!��ɫ
#define CYAN         RGB(0x00, 0xFF, 0xFF)
//!��ɫ
#define RED          RGB(0xFF, 0x00, 0x00)
//!��ɫ
#define MAGENTA      RGB(0xFF, 0x00, 0xFF)
//!��ɫ
#define YELLOW       RGB(0xFF, 0xFF, 0x00)
//!��ɫ
#define WHITE        RGB(0xFF, 0xFF, 0xFF)
//! @}

//////////////////////////////////////////////////////////////////////////
//
// ����ԭ������
//
//////////////////////////////////////////////////////////////////////////

/**
 * \addtogroup EggBasic
 * @{
 */

/** 
 * ��ʼʹ��Egg
 *
 * ��������ʾһ��Eggͼ�δ��ڣ���Ϊ�����ӡ��������Ƿ��εģ�-_-!�����������ƽ��
 * ֱ������ϵ�����½���Ϊ����ԭ��(0,0)����λ���ס�����ʹ��Egg�ṩ��������������
 * ���ڰڷ�egg������egg�ϻ滭��
 * <P> <b>�����ȵ��ô˺���һ�Σ���ֻ��һ�Σ��ſ���ʹ��Egg���������ܡ�</b>
 * <P>�����˳�ʱ��Eggռ�õ���Դ�ᱻ�Զ��ͷš�
 *
 * @param fWidth ָ�����ӿ�ȣ����ף�
 * @param fHeight ָ�����Ӹ߶ȣ����ף�
 */
void EggStart(double fWidth, double fHeight);

/**
 * ��ʾ�������ն˴���
 *
 * �ն˴��ں��ѿ��������ô˺����������������Դ��ն˴��ڶ�ȡ�û����룬Ҳ�����ڿ�
 * ���׶������淽������������Ϣ�����Ի�����Ҫ��ʾ��ʱ��
 *
 * @param bShow TRUE����ʾ��FALSE������
 */
void ShowConsoleWindow(BOOL bShow);

/**
 * �ƶ�����λ��
 *
 * �ı仭��λ�õ�����ָ���ľ������ꡣ
 *
 * @param x �»���λ�õ�X������
 * @param y �»���λ�õ�Y������
 */
void MovePen(double x, double y);

/**
 * λ�ƻ���λ��
 *
 * ������ָ����λ���ƶ�����λ�á�
 *
 * @param dx ��X���λ��
 * @param dy ��Y���λ��
 */
void OffsetPen(double dx, double dy);

/**
 * ��ֱ��
 *
 * �ӵ�ǰ����λ�ÿ�ʼ����X�᷽��λ��dx���ף���Y�᷽��λ��dy���ף���һ��ֱ�ߡ���
 * �߽�����ֱ�ߵ��յ㱻��Ϊ�µĻ���λ�á�
 *
 * @param dx X�᷽���λ��
 * @param dy Y�᷽���λ��
 * @see MovePen()
 */
void DrawLine(double dx, double dy);

/**
 * �����ַ��� 
 *
 * �˺���ʹ�õ�ǰ��ɫ�����壬�Ի���λ��Ϊ���Ͻǣ���ˮƽ��������ַ�����
 * ��ͼ��Ϻ󻭱�λ���Զ��ƶ����ַ��������Ͻǡ�
 *
 * @param pString �����Ƶ��ַ�������'\\0'Ϊ������
 */
void DrawString(char* pString);

/**
 * �õ��ַ������
 *
 * ����������pString�õ�ǰ���塢�ֺ���ʾ�������ڵĿ�ȡ�
 *
 * @param pString Ҫ������ַ���
 * @return ��ȣ����ף�
 * @see DrawString()
 */
double GetStringWidth(char* pString);

/**
 * ������
 *
 * �ӻ��ʵ�ǰλ�ÿ�ʼ����һ����rΪ�뾶����Բ���ߡ���������ڴ�����Բ��dStart��
 * �ȿ�ʼ������ʱ�뷽��ɨ��dSweep�ȡ�
 *
 * @param r �뾶
 * @param dStart ���߿�ʼ�Ƕ�
 * @param dSweep ����ɨ���ĽǶȡ�������ʾ����ʱ�뷽�򣬸�����ʾ��˳ʱ�뷽��
 * @see DrawEllipticalArc
 */
void DrawArc(double r, double dStart, double dSweep);

/**
 * ����Բ����
 *
 * �� DrawArc() һ����Ψһ��ͬ����������Ϊ��Բ���ߡ�
 * 
 * @param rx ����������Բ��X�᷽��İ뾶
 * @param ry ����������Բ��Y�᷽��İ뾶
 * @param dStart ���߿�ʼ�Ƕ�
 * @param dSweep ����ɨ���ĽǶȡ�������ʾ����ʱ�뷽�򣬸�����ʾ��˳ʱ�뷽��
 * @see DrawArc()
 */
void DrawEllipticalArc(double rx, double ry, double dStart, double dSweep);

//!@}

/**
 *\addtogroup EggInput
 * @{
 */

/**
 * �ȴ����¼�
 *
 * �����ȴ���ֱ�������¼������ŷ��ء�
 *
 * @return �����¼����ͣ����������¼���
 * - EXIT ���� �û�Ҫ���˳����򡣵���رմ��ڰ�ť��Alt+F4����ʹ��ֵ�����ء�
 * �����ߴ�ʱӦ���ͷ�ռ�õ�������Դ��Ȼ���˳�����
 * - TIMER ���� ��ʱ�����¼���
 * - MOUSEMOVE ���� ��걻�ƶ���ͨ�� GetMouseX() �� GetMouseY() ���Եõ�����ƶ�
 * ����λ�ã�
 * - KEYDOWN ���� ���̻���갴�������£�ͨ�� GetStruckKey() ����֪�����ĸ��������£�
 * - KEYUP ���� ���̻���갴�����ͷţ�ͨ�� GetStruckKey() ����֪�����ĸ��������£�
 *
 * @see EVENT_TYPE
 * @see GetStruckKey()
 * @see GetMouseX()
 * @see GetMouseY()
 * @see IsKeyDown()
 * @see WaitForExit()
 */
EVENT_TYPE WaitForEvent(void);

/**
 * �ȴ��˳�����
 *
 * ���û��رմ��ڣ��˺������ء�
 */
void WaitForExit(void);

/**
 * �жϰ����Ƿ����ڱ�����
 *
 * �ж�ָ���İ����Ƿ������ڰ���״̬�������ж϶�������Ƿ�ͬʱ����ʱ�ǳ����á�
 *
 * @param uVKCode ���жϵİ����������ֵ
 * @return TRUE���������ڰ���״̬��FALSE���������ڵ���״̬
 */
BOOL IsKeyDown(unsigned int uVKCode);

/**
 * �õ��������ļ��������ֵ
 *
 * �� WaitForEvent() ���ʹ�á���WaitForEvent() ����KEYDOWN��KEYUPʱ�����ô˺�
 * �����Եõ����ĸ��������������̺���갴�������������������
 *
 * @return �����ļ��������ֵ
 * @see WaitForEvent()
 */
unsigned int GetStruckKey(void);

/**
 * ���ָ�뵱ǰλ�õ�X����
 * 
 * �������ָ���������ڵ�ǰ��X���ꡣ
 * @return ����������ڵ�ǰ��X����
 *
 * @see GetMouseY()
 */
double GetMouseX(void);

/**
 * ���ָ�뵱ǰλ�õ�Y����
 * 
 * �������ָ���������ڵ�ǰ��Y���ꡣ
 * @return ����������ڵ�ǰ��Y����
 *
 * @see GetMouseX()
 */
double GetMouseY(void);
//! @}

/**
 * \defgroup EggAnimation ��������
 * ���к���ʵ����Egg�Ķ������ܡ�ͨ�����ǿ��Խ����µ�egg���ƶ�egg��λ����ʵ�ֶ�
 * ��Ч�����������ƿ�ʱ���������̶�������ʾ������
 *  @{
 */

/**
 * �µ���^_^
 *
 * Eggƽ̨��һ����ɫ���ǿ�������������������egg��ÿ��egg����һ�������Ļ�������
 * ������������滭�������ƶ�egg�������ڵ�λ�ã��ﵽ����Ч����<BR>
 * ����������һ����egg����λ������egg����㣬��С������һ�²���ȫ��������
 * ����egg��ȫ͸�������ε������½���egg�Զ���Ϊ�����
 *
 * @return �½�egg�ľ������Ϊ������ͼ�����Ĳ���ʹ�á�
 */
HEGG LayEgg(void);

/**
 * ���û��
 *
 * ����Ǹ���egg�����Ķ���
 *
 * @param hEgg ������
 */
void SetActiveEgg(HEGG hEgg);

/**
 * ���������ƶ�egg��ָ��λ��
 *
 * �½���eggȱʡ�����������ӡ����ô˺��������ƶ�egg�����Ͻǵ����ӵ�ָ��λ�á�
 *
 * @param x Ŀ����������ϵ�X������
 * @param y Ŀ����������ϵ�Y������
 * @see LayEgg()
 * @see OffsetEgg()
 */
void MoveEgg(double x, double y);

/**
 * �������ϰ�egg�ƶ�ָ���ľ���
 *
 * �����ӵ�X��λ��dx���ף���Y��λ��dy���ס�
 *
 * @param dx �����ӵ�X��λ�ƵĴ�С����ֵ��ʾ���������ƶ�����ֵ��ʾ�򸺷����ƶ���
 * ��ֵ��ʾ���ƶ���
 * @param dy �����ӵ�Y��λ�ƵĴ�С����ֵ��ʾ���������ƶ�����ֵ��ʾ�򸺷����ƶ���
 * ��ֵ��ʾ���ƶ���
 * @see LayEgg()
 * @see MoveEgg()
 */
void OffsetEgg(double dx, double dy);

/**
 * �������ڶ�ʱ��
 *
 * ��ʱ������һ�����㱨ʱ�����ӣ�ÿ��һСʱ����һ�Ρ���Egg�ṩ�Ķ�ʱ�����ܸ�ǿ
 * �������ָ������ı�ʱ���ڣ�Ȼ��������𣬰���������ڲ���һϵ�еĶ�ʱ�㡣
 * ������ʱ������ WaitForEvent() ����Ƿ񵽴ﶨʱ�㡣<br>
 * ���µ��ô˺�����������һ���µĶ�ʱ����ԭ��ʱ���Զ�ʧЧ��
 *
 * @param uMillisecond ������ʱ������ڣ���λ�Ǻ��루���鲻Ҫʹ��С��50�������
 *                     �ڣ���
 * @see StopTimer()
 * @see WaitForEvent()
 * @see WaitFor()
 */
void StartTimer(unsigned int uMillisecond);

/**
 * ֹͣ���ڶ�ʱ��
 *
 * �˺���ֹͣ��ʱ�������ٲ��������¼���
 *
 * @see StartTimer()
 * @see WaitForEvent()
 * @see WaitFor()
 */
void StopTimer(void);

/**
 * ��ʱ����
 *
 * �˺���ִ��uMillisecond����󷵻�TRUE�����ʱ��δ�����û��ر��˴��ڣ�����FALSE<BR>
 * <b>ע�⣺</b>���ô˺������൱�ڵ�����StopTimer()
 * 
 * @param uMillisecond �ȴ�ʱ�䣬��λ����
 * @return ʱ�䵽����TRUE��ʱ��δ���������ڱ��رշ���FALSE��
 * @see StartTimer()
 * @see StopTimer()
 * @see WaitForEvent()
 */
BOOL WaitFor(unsigned int uMillisecond);

//! @}

/**
 *\addtogroup EggAdvGraph
 * @{
 */
 

/**
 * ���û�����ɫ�Ϳ��
 *
 * ���ʵ�ȱʡ��ɫΪ��ɫ�����Ϊһ�����ء��ô˺����ı���ɫ�Ϳ�Ⱥ����еĺ�����
 * ͼ��������ʹ�ô����á�
 * @param color �µĻ�����ɫ������ʹ�ã�
 *      - BLACK ���� ��ɫ
 *      - DARK_BLUE ���� ����ɫ
 *      - DARK_GREEN ���� ����ɫ
 *      - DARK_CYAN ���� ����ɫ
 *      - DARK_RED ���� ���ɫ
 *      - DARK_MAGENTA ���� ����ɫ
 *      - DARK_YELLOW ���� ���ɫ
 *      - LIGHT_GRAY ���� ǳ��ɫ
 *      - DARK_GRAY ���� ���ɫ
 *      - BLUE ���� ��ɫ
 *      - GREEN ���� ��ɫ
 *      - CYAN ���� ��ɫ
 *      - RED ���� ��ɫ
 *      - MAGENTA ���� ��ɫ  
 *      - YELLOW ���� ��ɫ
 *      - WHITE ���� ��ɫ
 * @param fWidth ���ʿ�ȣ���λ����
 * @see SetPenColor
 * @see SetPenWidth
 */
void SetPen(unsigned long color, double fWidth);

/**
 * ���û�����ɫ
 *
 * ���ʵ�ȱʡ��ɫΪ��ɫ���ô˺����ı���ɫ�����еĻ�ͼ�����������ô���ɫ��
 * @param color �µĻ�����ɫ������ʹ�ã�
 *      - BLACK ���� ��ɫ
 *      - DARK_BLUE ���� ����ɫ
 *      - DARK_GREEN ���� ����ɫ
 *      - DARK_CYAN ���� ����ɫ
 *      - DARK_RED ���� ���ɫ
 *      - DARK_MAGENTA ���� ����ɫ
 *      - DARK_YELLOW ���� ���ɫ
 *      - LIGHT_GRAY ���� ǳ��ɫ
 *      - DARK_GRAY ���� ���ɫ
 *      - BLUE ���� ��ɫ
 *      - GREEN ���� ��ɫ
 *      - CYAN ���� ��ɫ
 *      - RED ���� ��ɫ
 *      - MAGENTA ���� ��ɫ  
 *      - YELLOW ���� ��ɫ
 *      - WHITE ���� ��ɫ
 * @see SetPen()
 */
void SetPenColor(unsigned long color);

/**
 * ���û��ʿ��
 *
 * ��Ⱥ����еĺ�����ͼ��������ʹ�ô����á�
 * @param fWidth ���ʿ�ȣ���λ����
 * @see SetPen
 * @see SetPenColor
 */
void SetPenWidth(double fWidth);

//! @}

#endif //_EGG_SUNNER_HIT
