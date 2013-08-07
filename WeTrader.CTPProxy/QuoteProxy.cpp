// This is the main DLL file.

#include "stdafx.h"
#include "string.h"
#include "iostream"

#include "QuoteProxy.h"
using namespace std;

CThostFtdcMdApi* md;
QuoteMdSpi* mdSpi;
char* brokerId;
char* userId;
char* passwd;
//回调事件
OnQuoteProxyCreated createdInvoke;
OnQuoteHeartBeatWarning heartBeatInvoke;
OnQuoteRspUserLogin rspUserLoginInvoke;
OnQuoteRspUserLogout rspUserLogoutInvoke;
OnQuoteRspError rspErrorInvoke;
OnQuoteRspSubMarketData rspSubMarketDataInvoke;
OnQuoteRspUnSubMarketData rspUnSubMarketDataInvoke;
OnQuoteRtnDepthMarketData  rtnDepthMarketDataInvoke;

void QuoteMdSpi::OnFrontConnected(){
	CThostFtdcReqUserLoginField f;
	memset(&f, 0, sizeof(f));
	strcpy_s(f.BrokerID, brokerId);
	strcpy_s(f.UserID, userId);
	strcpy_s(f.Password, passwd);
	md->ReqUserLogin(&f, ++nReq);
}
//心跳
void QuoteMdSpi::OnHeartBeatWarning(int nTimeLapse){
	if(heartBeatInvoke != NULL){
		heartBeatInvoke(nTimeLapse);
	}
}
///登录请求响应
void QuoteMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspUserLoginInvoke!=NULL){
		rspUserLoginInvoke(pRspUserLogin,pRspInfo,nRequestID,bIsLast);
	}
}
///登出请求响应
void QuoteMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspUserLogoutInvoke != NULL){
		rspUserLogoutInvoke(pUserLogout,pRspInfo,nRequestID,bIsLast);
	}
}
///错误应答
void QuoteMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspErrorInvoke != NULL){
		rspErrorInvoke(pRspInfo,nRequestID,bIsLast);
	}
}
///订阅行情应答
void QuoteMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(rspSubMarketDataInvoke != NULL){
		rspSubMarketDataInvoke(pSpecificInstrument,pRspInfo,nRequestID,bIsLast);
	}
}
///取消订阅行情应答
void QuoteMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if(rspUnSubMarketDataInvoke != NULL){
		rspUnSubMarketDataInvoke(pSpecificInstrument,pRspInfo,nRequestID,bIsLast);
	}
}
//返回数据响应
void QuoteMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData){
	if(rtnDepthMarketDataInvoke != NULL){
		rtnDepthMarketDataInvoke(pDepthMarketData);
	}
}

//注册创建完成后的事件
ExportAPI void __stdcall RegOnQuoteProxyCreated(OnQuoteProxyCreated e){
	createdInvoke=e;
}

//注册心跳事件
ExportAPI void __stdcall RegOnQuoteHeartBeatWarning(OnQuoteHeartBeatWarning e){ heartBeatInvoke = e;}

//注册用户登录之后事件
ExportAPI void __stdcall RegOnQuoteRspUserLogin(OnQuoteRspUserLogin e){ rspUserLoginInvoke = e;}

//注册用户登出之后事件
ExportAPI void __stdcall RegOnQuoteRspUserLogout(OnQuoteRspUserLogout e){ rspUserLogoutInvoke = e;}

//注册错误响应的事件
ExportAPI void __stdcall RegOnQuoteRspError(OnQuoteRspError e){ rspErrorInvoke = e;}

//注册订阅行情之后的事件
ExportAPI void __stdcall RegOnQuoteRspSubMarketData(OnQuoteRspSubMarketData e){ rspSubMarketDataInvoke = e;}

//注册退订行情之后的事件
ExportAPI void __stdcall RegOnQuoteRspUnSubMarketData(OnQuoteRspUnSubMarketData e){rspUnSubMarketDataInvoke = e;}

//注册收到行情数据后的事件
ExportAPI void __stdcall RegOnQuoteRtnDepthMarketData(OnQuoteRtnDepthMarketData e){rtnDepthMarketDataInvoke = e;}

//实例化
ExportAPI void CreateQuoteProxy(char* brokerid,char* userid,char* pwd){
	brokerId=brokerid;
	userId=userid;
	passwd=pwd;
	mdSpi = new QuoteMdSpi();
	md=CThostFtdcMdApi::CreateFtdcMdApi("./qlog");
	md->RegisterSpi((CThostFtdcMdSpi*)mdSpi);
	if(createdInvoke != NULL){
		createdInvoke();
	}
}

//注册前置机
ExportAPI void RegisterQuoteFront(char* fontaddr){
	md->RegisterFront(fontaddr);
}

//名称服务器网络地址
ExportAPI void RegisterQuoteNameServer(char* nsaddr){
	md->RegisterNameServer(nsaddr);
}

//初始化
ExportAPI void QuoteInit(){
	md->Init();
}

//订阅行情
ExportAPI void SubscribeMarketData(char* instrumentId){
	char*ppInst[1];
	ppInst[0]=instrumentId;
	md->SubscribeMarketData(ppInst,1);
}