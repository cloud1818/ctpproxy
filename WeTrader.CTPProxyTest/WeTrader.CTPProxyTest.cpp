// WeTrader.CTPProxyTest.cpp : main project file.

#include "stdafx.h"
#include "string.h"
#include "iostream"
#include "..\WeTrader.CTPProxy\QuoteProxy.h"
#include "..\WeTrader.CTPProxy\TraderProxy.h"
using namespace std;

#pragma comment(lib,"../Debug/WeTrader.CTPProxy.lib")


void __stdcall InitFinish(){
	
}

void __stdcall AfterUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(bIsLast){
		SubscribeMarketData("IF1308");
	}
}

void __stdcall ShowData(CThostFtdcDepthMarketDataField *p){
	cout<<p->InstrumentID<<"  "<<p->UpdateTime<<"  "<<p->LastPrice<<endl;
}

//int main(){
//	RegOnQuoteProxyCreated(InitFinish);
//	RegOnQuoteRtnDepthMarketData(ShowData);
//	RegOnQuoteRspUserLogin(AfterUserLogin);
//	///*char* frontAddress="tcp://ctpmn1-front1.citicsf.com:51213";
//	//char* brokeid="1017";
//	//char* uid="00000071";
//	//char* pwd="123456";*/
//	//char* frontAddress="tcp://180.169.30.170:41213";
//	//char* brokeid="8050";
//	//char* uid="00217850";
//	//char* pwd="990066";
//	//Init(frontAddress,brokeid,uid,pwd);
//	CreateQuoteProxy("1017","00000071","123456");
//	RegisterQuoteFront("tcp://115.238.106.252:41213");
//	QuoteInit();
//	getchar();
//	return 0;
//}

void __stdcall CrateTrader(){

}

void __stdcall TraderAuth(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	cout<<"Auth======="<<endl;
	cout<<"User Id: "+ *pRspAuthenticateField->UserID<<endl;
	cout<<"Info: "+ *pRspInfo->ErrorMsg<<endl;
}

void __stdcall AfterTraderUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	cout<<"User Login ============"<<endl;
	cout<<"Login Time : "+*pRspUserLogin->LoginTime<<endl;
	cout<<"SHFETime : " + *pRspUserLogin->SHFETime << endl;
	cout<<"MaxOrderRef: " + *pRspUserLogin->MaxOrderRef <<endl;
}

int main(){
	RegOnTraderProxyCreated(CrateTrader);
	RegOnTraderRspAuthenticate(TraderAuth);
	RegOnTraderRspUserLogin(AfterTraderUserLogin);
	
	CreateTraderProxy("1008","00000027","123456");
	RegisterTraderFront("tcp://115.238.106.252:41205");

	TraderInit();
	getchar();
	return 0;
}