import streamlit as st
import pandas as pd
import requests

st.title("🚀 AI Crypto Trading Dashboard")

# Binance API se live data fetch karna
url = "https://api.binance.com/api/v3/klines?symbol=BTCUSDT&interval=1d&limit=30"
res = requests.get(url).json()

# Closing prices nikal kar ek clean list banana
closing_prices = [float(candle[4]) for candle in res]

# Dashboard par live price dikhana
latest_price = closing_prices[-1]
st.metric("💰 Latest BTC Price", f"${latest_price:,.2f}")

# Line chart show karna
st.line_chart(closing_prices)

st.success("Dashboard successfully loaded!")
