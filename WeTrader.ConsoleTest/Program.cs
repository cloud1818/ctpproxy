using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using WeTrader.CTPApi;

namespace WeTrader.ConsoleTest {
    class Program {
        static void Main(string[] args) {
            try {
                TraderApi.RegOnHeartBeatWarning(HearBeating);
                TraderApi.RegOnRspAuthenticate(OnAuth);
                TraderApi.RegOnRspUserLogin(OnRspUserLogin);
                TraderApi.CreateProxy(Marshal.StringToHGlobalAnsi("1008"), Marshal.StringToHGlobalAnsi("00000027"), Marshal.StringToHGlobalAnsi("123456"));
                TraderApi.RegisterFront(Marshal.StringToHGlobalAnsi("tcp://115.238.106.252:41205"));
                TraderApi.Init();

                Console.Read();
            } catch (Exception ex) {
                Console.Read();
            }
        }

        private static void HearBeating(int timespan) {
            Console.WriteLine("Hear Beating " + timespan);
        }

        private static void OnAuth(
            ref CThostFtdcRspAuthenticateField rspAuthenticate,
            ref CThostFtdcRspInfoField rspInfo,
            int requestId,
            bool isLast) {
            Console.WriteLine("Auth==========");
            Console.WriteLine("User ID :" + rspAuthenticate.UserID);
            Console.WriteLine("ErrorMsg: " + rspInfo.ErrorMsg);
        }

        private static void OnRspUserLogin(
            ref CThostFtdcRspUserLoginField rspUserLogin, ref CThostFtdcRspInfoField rspInfo, int requestId, bool isLast) {
            if (isLast) {
                Console.WriteLine("User Login=========");
                Console.WriteLine("LoginTime: " + rspUserLogin.LoginTime);
                Console.WriteLine("SHFETime: " + rspUserLogin.SHFETime);
                Console.WriteLine("MaxOrderRef: " + rspUserLogin.MaxOrderRef);
                Console.WriteLine("Info:" + rspInfo.ErrorMsg);
            }
        }
    }
}
