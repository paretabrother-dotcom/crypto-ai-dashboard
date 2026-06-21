import streamlit as st

st.title("🚀 AI Crypto Trading Dashboard")

# Static safe data for display
btc_price = 64320.50

st.metric(label="💰 Latest BTC Price", value=f"${btc_price:,.2f}", delta="+2.4%")

# Simple list for line chart
chart_data = [63100, 62800, 63500, 64100, 64320]
st.line_chart(chart_data)

st.success("Dashboard successfully loaded and running!")
