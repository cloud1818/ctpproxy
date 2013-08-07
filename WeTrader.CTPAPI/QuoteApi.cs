using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace WeTrader.CTPApi {
    /// <summary>
    /// 行情数据API
    /// </summary>
    public static class QuoteApi {
        private const string DLLName = "WeTrader.CTPProxy.dll"; 
        /// <summary>
        /// 初始化完成后的委托
        /// </summary>
        /// <returns></returns>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnProxyCreated();
        /// <summary>
        /// 心跳事件
        /// </summary>
        /// <param name="timeLaspse"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnHeartBeatWarning(int timeLaspse);
        /// <summary>
        /// 登录事件
        /// </summary>
        /// <param name="rspUserLogin"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUserLogin(ref CThostFtdcRspUserLoginField rspUserLogin, ref CThostFtdcRspInfoField rspInfo, int requestId, bool isLast);
        /// <summary>
        /// 退出事件
        /// </summary>
        /// <param name="rspUserLogin"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUserLogout(ref CThostFtdcRspUserLoginField rspUserLogin, ref CThostFtdcRspInfoField rspInfo, int requestId, bool isLast);
        /// <summary>
        /// 错误响应
        /// </summary>
        /// <param name="rspInfo"></param>
        /// <param name="requestid"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspError(ref CThostFtdcRspInfoField rspInfo, int requestid, bool isLast);
        /// <summary>
        /// 订阅行情应答
        /// </summary>
        /// <param name="instrument"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspSubMarketData(
            ref CThostFtdcSpecificInstrumentField instrument,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast);
        /// <summary>
        /// 退订行情应答
        /// </summary>
        /// <param name="instrument"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUnSubMarketData(
            ref CThostFtdcSpecificInstrumentField instrument,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast);
        /// <summary>
        /// 接收行情数据的委托
        /// </summary>
        /// <param name="param"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField param);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnQuoteProxyCreated", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnProxyCreated(OnProxyCreated e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteHeartBeatWarning", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnHeartBeatWarning(OnHeartBeatWarning e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteRspUserLogin", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUserLogin(OnRspUserLogin e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteRspUserLogout", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUserLogout(OnRspUserLogout e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteRspError", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspError(OnRspError e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteRspSubMarketData", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnspSubMarketData(OnRspSubMarketData e);

        [DllImport(DLLName, EntryPoint = "RegOnQuoteRspUnSubMarketData", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUnSubMarketData(OnRspUnSubMarketData e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnQuoteRtnDepthMarketData", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRtnDepthMarketData(OnRtnDepthMarketData e);
        /// <summary>
        /// 创建代理实例
        /// </summary>
        /// <param name="brokerid"></param>
        /// <param name="userid"></param>
        /// <param name="pwd"></param>
        [DllImport(DLLName, EntryPoint = "CreateQuoteProxy", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateProxy(IntPtr brokerid, IntPtr userid, IntPtr pwd);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr"></param>
        [DllImport(DLLName, EntryPoint = "RegisterQuoteFront", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterFront(IntPtr addr);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr"></param>
        [DllImport(DLLName, EntryPoint = "RegisterQuoteNameServer", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterNameServer(IntPtr addr);
        /// <summary>
        /// 
        /// </summary>
        [DllImport(DLLName, EntryPoint = "QuoteInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Init();
        /// <summary>
        /// 
        /// </summary>
        /// <param name="instrumentId"></param>
        [DllImport(DLLName, EntryPoint = "SubscribeMarketData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SubscribeMarketData(IntPtr instrumentId);
    }
}
