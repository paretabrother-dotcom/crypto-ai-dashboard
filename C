import streamlit as st
import pandas as pd
import requests
import matplotlib.pyplot as plt

st.title("🚀 AI Crypto Trading Signal Dashboard")
st.write("Bitcoin (BTC) Real-Time Data, Advanced Indicators & AI Signals")

url = "https://api.binance.com/api/v3/klines"
params = {"symbol": "BTCUSDT", "interval": "1d", "limit": "100"}
response = requests.get(url, params=params).json()

columns = ['Open Time', 'Open', 'High', 'Low', 'Close', 'Volume', 'Close Time', 'Asset Volume', 'Trades', 'Buy Base', 'Buy Quote', 'Ignore']
df = pd.DataFrame(response, columns=columns)
df['Date'] = pd.to_datetime(df['Open Time'], unit='ms')
df['Close'] = df['Close'].astype(float)

df['SMA_5'] = df['Close'].rolling(window=5).mean()

delta = df['Close'].diff()
gain = (delta.where(delta > 0, 0)).rolling(window=14).mean()
loss = (-delta.where(delta < 0, 0)).rolling(window=14).mean()
rs = gain / loss
df['RSI'] = 100 - (100 / (1 + rs))

latest_close = df['Close'].iloc[-1]
latest_sma = df['SMA_5'].iloc[-1]
latest_rsi = df['RSI'].iloc[-1]

col1, col2 = st.columns(2)
with col1:
    st.metric(label="💰 Latest BTC Price", value=f"${latest_close:,.2f}")
with col2:
    st.metric(label="📈 Current RSI (14)", value=f"{latest_rsi:.2f}")

st.subheader("📢 Live AI Trading Signal")
if latest_rsi < 35 and latest_close > latest_sma:
    st.success("🟢 STRONG BUY SIGNAL: Market Oversold hai aur trend upar ja raha hai!")
elif latest_rsi > 65 and latest_close < latest_sma:
    st.error("🔴 STRONG SELL SIGNAL: Market Overbought hai aur trend gir raha hai!")
elif latest_rsi < 40:
    st.info("🟢 WEAK BUY: Risk kam hai, entry li ja sakti hai.")
elif latest_rsi > 60:
    st.warning("🔴 WEAK SELL: Alert rahein, profit book karne ka time ho sakta hai.")
else:
    st.info("⚪ HOLD SIGNAL: Market sideways hai, abhi wait karein.")

st.subheader("📊 Price Chart with Technical Trend")
fig, ax = plt.subplots(figsize=(10, 4))
ax.plot(df['Date'], df['Close'], color='cyan', label='BTC Price', linewidth=2)
ax.plot(df['Date'], df['SMA_5'], color='orange', label='SMA 5', linestyle='--')
ax.grid(True, alpha=0.2)
ax.legend()
fig.patch.set_facecolor('#0e1117')
ax.set_facecolor('#0e1117')
ax.xaxis.label.set_color('white')
ax.yaxis.label.set_color('white')
ax.tick_params(colors='white')
st.pyplot(fig)
