import random

# Define the stock symbol and years
symbol = "AAPL"
years = list(range(2010, 2023))

# Get the number of transactions from the user
num_transactions = int(input("Enter the number of buy and sell transactions: "))

# Generate random buy and sell transactions
transaction_history = []

# Start with the initial "Buy" transaction
initial_buy = f"{symbol} 1 1 2010 Buy 100 10000.00"
transaction_history.append(initial_buy)

for _ in range(num_transactions - 1):  # Generate the remaining transactions
    year = random.choice(years)
    month = random.randint(1, 12)
    day = random.randint(1, 28)
    buy_sell = random.choice(["Buy", "Sell"])
    shares = random.randint(10, 200)
    amount = round(random.uniform(1000, 50000), 2)
    
    transaction = f"{symbol} {day} {month} {year} {buy_sell} {shares} {amount}"
    transaction_history.append(transaction)

# Save the transactions to a text file
output_file = "transaction_history.txt"
with open(output_file, "w") as file:
    for transaction in transaction_history:
        file.write(transaction + "\n")

print(f"Generated {num_transactions} buy/sell transactions and saved as '{output_file}'.")

