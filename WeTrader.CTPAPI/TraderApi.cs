using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace WeTrader.CTPApi {
    /// <summary>
    /// CTP交易API
    /// </summary>
    public static class TraderApi {
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
        /// 客户端认证响应委托
        /// </summary>
        /// <param name="rspAuthenticate"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspAuthenticate(
            ref CThostFtdcRspAuthenticateField rspAuthenticate,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast);
        /// <summary>
        /// 登录请求响应委托
        /// </summary>
        /// <param name="rspUserLogin"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUserLogin(
            ref CThostFtdcRspUserLoginField rspUserLogin, ref CThostFtdcRspInfoField rspInfo, int requestId, bool isLast
            );
        /// <summary>
        /// 用户登出委托
        /// </summary>
        /// <param name="userLogout"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUserLogout(
            ref CThostFtdcUserLogoutField userLogout, ref CThostFtdcRspInfoField rspInfo, int requestId, bool isLast);
        /// <summary>
        /// 用户口令更新响应委托
        /// </summary>
        /// <param name="userPassword"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspUserPasswordUpdate(
            ref CThostFtdcUserPasswordUpdateField userPassword,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast);
        /// <summary>
        /// 资金账户口令更新响应委托
        /// </summary>
        /// <param name="tradingAccountPassword"></param>
        /// <param name="rspInfo"></param>
        /// <param name="requestId"></param>
        /// <param name="isLast"></param>
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void OnRspTradingAccountPasswordUpdate(
            ref CThostFtdcTradingAccountPasswordUpdateField tradingAccountPassword,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnQuoteProxyCreated", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnProxyCreated(OnProxyCreated e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderHeartBeatWarning", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnHeartBeatWarning(OnHeartBeatWarning e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderRspAuthenticate", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspAuthenticate(OnRspAuthenticate e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderRspUserLogin", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUserLogin(OnRspUserLogin e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderRspUserLogout", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUserLogout(OnRspUserLogout e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderRspUserPasswordUpdate", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspUserPasswordUpdate(OnRspUserPasswordUpdate e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        [DllImport(DLLName, EntryPoint = "RegOnTraderRspTradingAccountPasswordUpdate", CallingConvention = CallingConvention.StdCall)]
        public static extern void RegOnRspTradingAccountPasswordUpdate(OnRspTradingAccountPasswordUpdate e);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="brokerid"></param>
        /// <param name="userid"></param>
        /// <param name="pwd"></param>
        [DllImport(DLLName, EntryPoint = "CreateTraderProxy", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateProxy(IntPtr brokerid, IntPtr userid, IntPtr pwd);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr"></param>
        [DllImport(DLLName, EntryPoint = "RegisterTraderFront", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterFront(IntPtr addr);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="addr"></param>
        [DllImport(DLLName, EntryPoint = "RegisterTraderNameServer", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterNameServer(IntPtr addr);
        /// <summary>
        /// 
        /// </summary>
        [DllImport(DLLName, EntryPoint = "TraderInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Init();
    }
}
