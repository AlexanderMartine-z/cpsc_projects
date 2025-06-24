import yfinance as yf
import pandas as pd

ticker = "^GSPC"
start_date = "2024-04-28"
end_date = "2025-04-28"

data = yf.download(ticker,start=start_date,end=end_date)

csv_filename = "S&PData.csv"

data.to_csv(csv_filename)

print(f"Saved historical data for {ticker} from {start_date} to {end_date} as '{csv_filename}'.")
