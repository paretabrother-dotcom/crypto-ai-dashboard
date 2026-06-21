import streamlit as st
import pandas as pd
import requests

st.title("🚀 AI Crypto Trading Dashboard")

url = "https://api.binance.com/api/v3/klines?symbol=BTCUSDT&interval=1d&limit=30"
res = requests.get(url).json()
df = pd.DataFrame(res)[4].astype(float)

st.metric("💰 Latest BTC Price", f"${df.iloc[-1]:,.2f}")
st.line_chart(df)

st.success("Dashboard successfully loaded without external modules!")
