import streamlit as st
import pandas as pd
import requests
from twilio.rest import Client

st.title("🚀 AI Crypto Trading Dashboard")
sid = st.secrets["TWILIO_SID"]
tok = st.secrets["TWILIO_TOKEN"]
to_num = st.secrets["TO_WHATSAPP"]

url = "https://api.binance.com/api/v3/klines?symbol=BTCUSDT&interval=1d&limit=30"
res = requests.get(url).json()
df = pd.DataFrame(res)[4].astype(float)

st.metric("💰 Latest BTC Price", f"${df.iloc[-1]:,.2f}")
st.line_chart(df)

if st.button("📲 Test Send WhatsApp Alert"):
    c = Client(sid, tok)
    c.messages.create(body=f"BTC Price Alert: ${df.iloc[-1]:,.2f}", from_="whatsapp:+14155238886", to=to_num)
    st.success("Alert Sent!")
