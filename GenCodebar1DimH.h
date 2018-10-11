#ifndef __GEN_CODEBAR_1_DIM_H_H__
#define __GEN_CODEBAR_1_DIM_H_H__
//////////////////////////////////////////////////////////////
/*////////////////////////////////////////////////////////////
		GenCodebar1Dim.dll ���ڶԳ���1ά�������ɽ��з�װ��
	�Ա�򻯵����ߡ�
	Designed by Vinca		-------2006/9/05
////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////
////////Լ�������нӿڲ������ڴ���ɺ��������߽��з������ͷ�
//////////////�������ֽ��У�bit7��1��ʾ����0��ʾ��
//							bit6��1��ʾ��ӳ�������0��ʾ����ӳ�
//					--------------��Code39�롢Code39��չ��������Bit����
//					------------------Bit1��Bit0���壺
//					-----------------------------00��ʾλ��(�������ַ���϶)
//					-----------------------------01��ʾ��
//					-----------------------------10��ʾ��
//					--------------��Inter25��������Bit����
//					------------------Bit1��Bit0���壺
//					-----------------------------01��ʾ��
//					-----------------------------10��ʾ��
//39��(������չ39��)��Դ�ļ�˵����0�пա�1���ա�2������3����
////////������������ֵ���壺
//0		����	�����ɹ�
//////
//-1		����	δ֪����
//-2		����	��ڲ���ָ��Ƿ�
//-3		����	�������Ͳ�֧��
//-4		����	��ڲ����Ƿ�
//-5		����	������ʼ��ʧ�ܣ���Դ����ʧ��
//-6		����	��������ʧ�ܣ�δ֪����
//-7		����	��������ʧ�ܣ���ڲ������ֲ�ƥ���������ɹ���
//-8		����	������Դ����
//-9		����	��������ʧ�ܣ���ڲ������Ȳ�ƥ��(�������������ز�������)
//////
//1			����	��������ʧ�ܣ�Ԥ�����ڴ治��
////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////
////Code128�롢Ean128��˵����
////	4��ת���ַ���0xF1��0xF2��0xF3��0xF4��0xF5��0xF6��0xF7
////	0xF1��ʾCODEA��0xF2��ʾCODEB��0xF3��ʾCODEC��0xF4��ʾSHIFT
////	0xF5��ʾFNC1��0xF6��ʾFNC2��0xF7��ʾFNC3��0xF8��ʾFNC4
////ע�����ַ�Ϊת���ַ������壺0xF1��ʾSTARTA��0xF2��ʾSTARTB��0xF3��ʾSTARTC
////	���ַ���Ϊת���ַ��������Code128 Auto�Ĺ��������ʼ�ַ���STARTA��STARTB��STARTC
////Code128 Auto���в���������ת���ַ�	
//////////////////////////////////////////////////////////////
//֧�ֵ�һά��������
enum{
	eCodebar1Dim_UpcA=1,//UpcA
	eCodebar1Dim_UpcE,//UpcE
	eCodebar1Dim_Ean13,//EAN13
	eCodebar1Dim_Ean8,//EAN8
	eCodebar1Dim_Code128,//Code128
	eCodebar1Dim_Ean128,//EAN128
	eCodebar1Dim_Code128Auto,//Code128Auto
	eCodebar1Dim_Code39,//Code39
	eCodebar1Dim_Code39Ex,//Code39Ex
	eCodebar1Dim_Inter25,//Inter25
};

//�����������ɺ����ӿ���ڡ����ڲ�������
typedef struct ICODEBAR1{
	long _type;//һά��������
	struct{
		////��ڲ���
		long _i_nSrcSize;//ԭ�ַ����ַ�����
		BYTE* _i_lpcbSrc;//ԭ�ַ�������
		long _i_nRetBinaryBuffSize;//�����������ڴ���ֽڴ�С
		long _i_nRetStrBuffSize;//�����ַ����ڴ���ֽڴ�С
		union{//ĳЩ����Ķ��⸽����ڲ���
			DWORD _dw39;//39�븽�Ӳ�����Bit0Ϊ1��ʾ��ҪУ�飬Ϊ0���ʾ����У��
			DWORD _dw25;//25�븽�Ӳ�����Bit0Ϊ1��ʾ��ҪУ�飬Ϊ0���ʾ����У��
		} _uExtraInput;
		////���ڲ���(������-9����ʱ��_nRltBinarySize��ʾʵ���������������ַ�������)
		long _o_nRltBinarySize;//�������ɵĶ������ִ����ֽڴ�С
		BYTE* _i_lpcbRetBinaryBuff;//�������ɵĶ������ִ�
		long _o_nRltIndexStart;//ָʾ_lpszSrc��_lpszRetStrBuff�е���ʼ����(��ֵ0)
		long _o_nRltStrSize;//�������ɵ������ַ������ֽڴ�С
		BYTE* _i_lpcbRetStrBuff;//�������ɵ������ַ���(ֻ����У��λʱ�����÷�����)
	} _s_value;
} ICODEBAR1;

//////�����ӿ�����
class IGenCodebar1Dim{
public:
	////��ȡ������Ϣ
	LPCSTR GetErrInfo(long errNo, long nResourceType){
		if( !LoadLib() )
			return (LPCSTR) NULL;
		return (((LPCSTR (__stdcall*)(long,long)) m_pFunc[0])(errNo,nResourceType));
	}
	////��������
	long GenCodebar(LPVOID lpValueSrcRet){
		if( !LoadLib() )
			return -1;
		return (((long (__stdcall*)(LPVOID)) m_pFunc[1])(lpValueSrcRet));
	}
	////
	IGenCodebar1Dim(){
		Clear();
	}
	~IGenCodebar1Dim(){
		ReleaseLib();
	}
	void ReleaseLib(){
		if( m_hLib ) ::FreeLibrary(m_hLib);
		Clear();
	}
	
private:
	void Clear(){
		memset(this,0,sizeof(*this));
	}
	BOOL LoadLib(){
		if( m_hLib )
			return TRUE;
		m_hLib=::LoadLibrary(TEXT("GenCodebar1Dim.dll"));
		if( !m_hLib ){
			OutputDebugString(TEXT("Can't find GenCodebar1Dim.dll!\n"));
			return FALSE;
		}
		BOOL bOk=TRUE;
		for( int i=0;i<2;i++ ){
			m_pFunc[i]=(DWORD) ::GetProcAddress((HMODULE) m_hLib,(LPCSTR) (MAKELONG(i+1,0)));
			if( 0==m_pFunc[i] ) bOk=FALSE;
		}
		if( !bOk ){
			OutputDebugString(TEXT("Incorrect version of GenCodebar1Dim.dll!\n"));
			ReleaseLib();
			return FALSE;
		}
		return TRUE;
	}
	
	////////////////
	DWORD m_pFunc[2];
	HINSTANCE m_hLib;
};
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
#endif