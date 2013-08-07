// WeTrader.CTPProxy.h

#pragma once
#include "QuoteMdSpi.h"

#define ExportAPI  extern "C" _declspec(dllexport)

//初始化完成后的委托
typedef void (__stdcall *OnQuoteProxyCreated)(void);

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
typedef void (__stdcall *OnQuoteHeartBeatWarning)(int nTimeLapse);

//完成登录之后的委托
typedef void (__stdcall *OnQuoteRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//退出登录之后的委托
typedef void (__stdcall *OnQuoteRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//错误应答
typedef void (__stdcall *OnQuoteRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//订阅行情应答
typedef void (__stdcall *OnQuoteRspSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//退订行情应答
typedef void (__stdcall *OnQuoteRspUnSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

//收到数据后的委托
typedef void (__stdcall *OnQuoteRtnDepthMarketData)(CThostFtdcDepthMarketDataField *p);

//注册初始化完成后的事件
ExportAPI void __stdcall RegOnQuoteProxyCreated(OnQuoteProxyCreated e);

//注册心跳事件
ExportAPI void __stdcall RegOnQuoteHeartBeatWarning(OnQuoteHeartBeatWarning e);

//注册用户登录之后事件
ExportAPI void __stdcall RegOnQuoteRspUserLogin(OnQuoteRspUserLogin e);

//注册用户登出之后事件
ExportAPI void __stdcall RegOnQuoteRspUserLogout(OnQuoteRspUserLogout e);

//注册错误响应的事件
ExportAPI void __stdcall RegOnQuoteRspError(OnQuoteRspError e);

//注册订阅行情之后的事件
ExportAPI void __stdcall RegOnQuoteRspSubMarketData(OnQuoteRspSubMarketData e);

//注册退订行情之后的事件
ExportAPI void __stdcall RegOnQuoteRspUnSubMarketData(OnQuoteRspUnSubMarketData e);

//注册收到行情数据后的事件
ExportAPI void __stdcall RegOnQuoteRtnDepthMarketData(OnQuoteRtnDepthMarketData e);


//实例化
ExportAPI void CreateQuoteProxy(char* brokerid,char* userid,char* pwd);

///<summary>
/// 注册前置机地址
///</summary>
///<param name="fontaddr">
/// 前置机网络地址
/// 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。
/// “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
///</param>
ExportAPI void RegisterQuoteFront(char* fontaddr);

///<summary>
/// 注册名称服务器网络地址
///</summary>
///<param name="nsaddr">
/// 服务器网络地址
/// @remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
/// @remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
/// @remark RegisterNameServer优先于RegisterFront
///</param>
ExportAPI void RegisterQuoteNameServer(char* nsaddr);

//API初始化
ExportAPI void QuoteInit();

//订阅行情
ExportAPI void SubscribeMarketData(char* instrumentId);