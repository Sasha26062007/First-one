import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os

st.set_page_config(layout="wide", page_title="Lab 5 Dashboard")

@st.cache_data
def load_data():
    if os.path.exists("lab2_data.csv"):
        return pd.read_csv("lab2_data.csv")
    else:
        p_list = [f"Province {i}" for i in range(1, 26)]
        data = []
        for p in p_list:
            for y in range(2015, 2021):
                for w in range(1, 53):
                    data.append([p, y, w, np.random.uniform(0, 100), np.random.uniform(0, 100), np.random.uniform(0, 100)])
        return pd.DataFrame(data, columns=['Province_Name', 'year', 'week', 'VCI', 'TCI', 'VHI'])

df = load_data()

def reset_state():
    keys_to_reset = ['idx_val', 'prov_val', 'weeks_val', 'years_val', 'asc_val', 'desc_val']
    for key in keys_to_reset:
        if key in st.session_state:
            del st.session_state[key]

col1, col2 = st.columns([1, 3])

with col1:
    st.header("Parameters")
    
    idx = st.selectbox("Select Index", ["VCI", "TCI", "VHI"], key="idx_val")
    prov = st.selectbox("Select Province", df['Province_Name'].unique(), key="prov_val")
    
    min_w, max_w = int(df['week'].min()), int(df['week'].max())
    weeks = st.slider("Weeks Interval", min_w, max_w, (min_w, max_w), key="weeks_val")
    
    min_y, max_y = int(df['year'].min()), int(df['year'].max())
    years = st.slider("Years Interval", min_y, max_y, (min_y, max_y), key="years_val")
    
    asc = st.checkbox("Sort Ascending", key="asc_val")
    desc = st.checkbox("Sort Descending", key="desc_val")
    
    if asc and desc:
        st.warning("Both sorting methods enabled. Reverting to original order.")
        asc = False
        desc = False
        
    st.button("Reset Filters", on_click=reset_state)

mask = (df['Province_Name'] == prov) & (df['week'] >= weeks[0]) & (df['week'] <= weeks[1]) & (df['year'] >= years[0]) & (df['year'] <= years[1])
filtered_df = df[mask].copy()

if asc:
    filtered_df = filtered_df.sort_values(by=idx, ascending=True)
elif desc:
    filtered_df = filtered_df.sort_values(by=idx, ascending=False)

with col2:
    tab1, tab2, tab3 = st.tabs(["Data Table", "Time Series Plot", "Province Comparison"])
    
    with tab1:
        st.dataframe(filtered_df, use_container_width=True)
        
    with tab2:
        fig1, ax1 = plt.subplots(figsize=(10, 5))
        filtered_df['Time'] = filtered_df['year'].astype(str) + "-W" + filtered_df['week'].astype(str)
        sns.lineplot(data=filtered_df, x='Time', y=idx, ax=ax1, color="blue")
        ax1.set_xticks(ax1.get_xticks()[::max(1, len(filtered_df)//10)])
        plt.xticks(rotation=45)
        ax1.set_title(f"{idx} over Time for {prov}")
        st.pyplot(fig1)
        
    with tab3:
        fig2, ax2 = plt.subplots(figsize=(10, 5))
        comp_mask = (df['week'] >= weeks[0]) & (df['week'] <= weeks[1]) & (df['year'] >= years[0]) & (df['year'] <= years[1])
        comp_df = df[comp_mask]
        sns.boxplot(data=comp_df, x='Province_Name', y=idx, ax=ax2, hue='Province_Name', legend=False)
        plt.xticks(rotation=90)
        ax2.set_title(f"{idx} Distribution: {prov} vs All Other Provinces")
        st.pyplot(fig2)
