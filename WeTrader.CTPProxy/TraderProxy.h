#pragma once
#include "TraderSpi.h"

#define ExportAPI  extern "C" _declspec(dllexport)

///初始化完成后的委托
typedef void (__stdcall *OnTraderProxyCreated)(void);
///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
typedef void (__stdcall *OnTraderHeartBeatWarning)(int nTimeLapse);
///客户端认证响应
typedef void (__stdcall *OnTraderRspAuthenticate)(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///登录请求响应
typedef void (__stdcall *OnTraderRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//登出请求响应
typedef void (__stdcall *OnTraderRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//用户口令更新请求响应
typedef void (__stdcall *OnTraderRspUserPasswordUpdate)(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
//资金账户口令更新请求响应
typedef void (__stdcall *OnTraderRspTradingAccountPasswordUpdate)(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


///注册初始化完成后的事件
ExportAPI void __stdcall RegOnTraderProxyCreated(OnTraderProxyCreated e);
///注册心跳事件
ExportAPI void __stdcall RegOnTraderHeartBeatWarning(OnTraderHeartBeatWarning e);
///注册客户端认证响应事件
ExportAPI void __stdcall RegOnTraderRspAuthenticate(OnTraderRspAuthenticate e);
///注册登录请求响应事件
ExportAPI void __stdcall RegOnTraderRspUserLogin(OnTraderRspUserLogin e);
///注册登出请求响应事件
ExportAPI void __stdcall RegOnTraderRspUserLogout(OnTraderRspUserLogout e);
///注册用户口令更新响应事件
ExportAPI void __stdcall RegOnTraderRspUserPasswordUpdate(OnTraderRspUserPasswordUpdate e);
///注册资金账户口令更新请求响应事件
ExportAPI void __stdcall RegOnTraderRspTradingAccountPasswordUpdate(OnTraderRspTradingAccountPasswordUpdate e);

//创建实例
ExportAPI void CreateTraderProxy(char* brokerid,char* userid,char* pwd);
//注册交易前端
ExportAPI void RegisterTraderFront(char* fontaddr);
//注册交易
ExportAPI void RegisterTraderNameServer(char* fontaddr);
//初始化
ExportAPI void TraderInit();