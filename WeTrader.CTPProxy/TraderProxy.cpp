#include "stdafx.h"
#include "string.h"
#include "iostream"

#include "TraderProxy.h"
using namespace std;

CThostFtdcTraderApi* traderApi; 
TraderSpi* traderSpi;
char* traderbrokerId;
char* traderuserId;
char* traderpasswd;

OnTraderProxyCreated traderCreatedInvoke;//创建
OnTraderHeartBeatWarning traderHeartBeatInvoke;//心跳
OnTraderRspAuthenticate traderRspAuthenicateInvoke;//客户端验证
OnTraderRspUserLogin traderRspUserLoginInvoke;//登录
OnTraderRspUserLogout traderRspUserLogoutInvoke;//登出
OnTraderRspUserPasswordUpdate traderRspUserPwdUpdateInvoke;//用户口令更新
OnTraderRspTradingAccountPasswordUpdate traderRspTradingAccoutPwdUpdateInvoke;//资金账号口令更新

void TraderSpi::OnFrontConnected(){
	CThostFtdcReqUserLoginField f;
	memset(&f, 0, sizeof(f));
	strcpy_s(f.BrokerID, traderbrokerId);
	strcpy_s(f.UserID, traderuserId);
	strcpy_s(f.Password, traderpasswd);
	traderApi->ReqUserLogin(&f, ++nReq);
}

void TraderSpi::OnHeartBeatWarning(int nTimeLapse){
	if(traderHeartBeatInvoke != NULL){
		traderHeartBeatInvoke(nTimeLapse);
	}
}

void TraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserLoginInvoke!=NULL){
		traderRspUserLoginInvoke(pRspUserLogin,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserLogoutInvoke!=NULL){
		traderRspUserLogoutInvoke(pUserLogout,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspUserPwdUpdateInvoke!=NULL){
		traderRspUserPwdUpdateInvoke(pUserPasswordUpdate,pRspInfo,nRequestID,bIsLast);
	}
}

void TraderSpi::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	if(traderRspTradingAccoutPwdUpdateInvoke != NULL){
		traderRspTradingAccoutPwdUpdateInvoke(pTradingAccountPasswordUpdate,pRspInfo,nRequestID,bIsLast);
	}
}

//注册创建完成后的事件
ExportAPI void __stdcall RegOnTraderProxyCreated(OnTraderProxyCreated e){
	traderCreatedInvoke=e;
}

///注册心跳事件
ExportAPI void __stdcall RegOnTraderHeartBeatWarning(OnTraderHeartBeatWarning e){
	traderHeartBeatInvoke=e;
}
///注册客户端认证响应事件
ExportAPI void __stdcall RegOnTraderRspAuthenticate(OnTraderRspAuthenticate e){
	traderRspAuthenicateInvoke=e;
}
///注册登录请求响应事件
ExportAPI void __stdcall RegOnTraderRspUserLogin(OnTraderRspUserLogin e){
	traderRspUserLoginInvoke=e;
}
///注册登出请求响应事件
ExportAPI void __stdcall RegOnTraderRspUserLogout(OnTraderRspUserLogout e){
	traderRspUserLogoutInvoke=e;
}
///注册用户口令更新响应事件
ExportAPI void __stdcall RegOnTraderRspUserPasswordUpdate(OnTraderRspUserPasswordUpdate e){
	traderRspUserPwdUpdateInvoke=e;
}
///注册资金账户口令更新请求响应事件
ExportAPI void __stdcall RegOnTraderRspTradingAccountPasswordUpdate(OnTraderRspTradingAccountPasswordUpdate e){
	traderRspTradingAccoutPwdUpdateInvoke=e;
}

//创建实例
ExportAPI void CreateTraderProxy(char* brokerid,char* userid,char* pwd){
	traderbrokerId=brokerid;
	traderuserId=userid;
	traderpasswd=pwd;
	traderSpi= new TraderSpi();
	traderApi=CThostFtdcTraderApi::CreateFtdcTraderApi("./tlog");
	traderApi->RegisterSpi((CThostFtdcTraderSpi*)traderSpi);
	if(traderCreatedInvoke!=NULL){
		traderCreatedInvoke();
	}
}
//注册交易前端
ExportAPI void RegisterTraderFront(char* fontaddr){
	traderApi->RegisterFront(fontaddr);
}
//注册交易
ExportAPI void RegisterTraderNameServer(char* fontaddr){
	traderApi->RegisterNameServer(fontaddr);
}
//初始化
ExportAPI void TraderInit(){
	traderApi->Init();
}