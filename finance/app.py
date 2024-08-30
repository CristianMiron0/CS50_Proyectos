import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    shares = db.execute("SELECT * FROM total_stock WHERE user_id = ?", session["user_id"])
    userCash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    totalCash = 0
    stockPrice = None
    stockInfo = None
    totalPrice = 0

    if shares:
        for share in shares:
            stockInfo = lookup(share["stock"])
            if stockInfo and "price" in stockInfo:
                stockPrice = stockInfo["price"]
                numberShares = share["number"]
                totalPrice = stockPrice * numberShares
                totalCash = totalCash + totalPrice

    if userCash:
        cash = userCash[0]["cash"]

    total = totalCash + cash

    return render_template("index.html", shares=shares, stockPrice=stockPrice, stockInfo=stockInfo, cash=cash, totalPrice=totalPrice, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        numberShares = request.form.get("shares")

        if not symbol:
            return apology("Symbol does not exist", 400)

        stock = lookup(symbol)
        if stock is None:
            return apology("Symbol does not exist", 400)

        try:
            numberShares = int(numberShares)
        except ValueError:
            return apology("Number lower than 1", 400)

        if numberShares <= 0:
            return apology("Number lower than 1", 400)

        price = stock["price"]
        priceShares = float(price) * numberShares

        money = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        money = money[0]["cash"]

        if float(priceShares) > float(money):
            return apology("Not enough money", 400)

        existingPurchase = db.execute(
            "SELECT * FROM purchases WHERE user_id = ? AND stock = ? AND purchase_date = CURRENT_DATE", session["user_id"], symbol
            )

        if existingPurchase:
            return apology("Purchase already exists", 400)

        db.execute(
            "INSERT INTO purchases (user_id, stock, price, number) VALUES (?, ?, ?, ?)", session["user_id"], symbol, priceShares, numberShares
        )

        rows_affected = db.execute(
            "UPDATE total_stock SET number = number + ? WHERE user_id = ? AND stock = ?", numberShares, session["user_id"], symbol
            )

        if rows_affected == 0:
            db.execute(
                "INSERT INTO total_stock (user_id, stock, number) VALUES (?, ?, ?)", session["user_id"], symbol, numberShares
                )

        newMoney = float(money) - float(priceShares)
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", newMoney, session["user_id"]
        )

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    shares = db.execute("SELECT * FROM purchases")

    return render_template("history.html", shares=shares)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol = symbol.upper()

        if not symbol:
            return apology("Symbol does not exist", 400)

        try:
            stock = lookup(symbol)
            if stock is None:
                raise ValueError("Symbol does not exist")
        except ValueError:
            return apology("Symbol does not exist", 400)

        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")

@app.route("/new_password", methods=["GET", "POST"])
def newPassword():
    """Change password"""
    if request.method == "POST":
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        newPassword = request.form.get("newPassword")

        if not password:
            return apology("must provide password", 400)

        if not newPassword:
            return apology("must provide a new password", 400)

        if not confirmation or password != confirmation:
            return apology("password do not match", 400)

        userHash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        hash = userHash[0]['hash']

        if not check_password_hash(hash, password):
            return apology("incorrect password", 400)

        newHash = generate_password_hash(newPassword)

        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?", newHash, session["user_id"]
            )

        return redirect("/")

    else:
        return render_template("new_password.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        if not password:
            return apology("must provide password", 400)

        if not confirmation or password != confirmation:
            return apology("password do not match", 400)

        hPassword = generate_password_hash(password)

        try:
            db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, hPassword
        )
        except ValueError:
            return apology("username already in use", 400)

        return redirect("login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    allShares = db.execute(
        "SELECT stock FROM total_stock WHERE user_id = ?", session["user_id"]
        )

    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        sellShares = request.form.get("shares")

        if not symbol:
            return apology("Symbol does not exist", 400)

        try:
            sellShares = int(sellShares)
        except ValueError:
            return apology("Number lower than 1", 400)

        if sellShares <= 0:
            return apology("Number lower than 1", 400)

        shares = db.execute(
            "SELECT number FROM total_stock WHERE user_id = ? and stock = ?", session["user_id"], symbol
            )

        if not shares:
            return apology("You dont own any shares in this stock", 400)

        currentShares = shares[0]['number']

        if sellShares > currentShares:
            return apology("You dont own that many shares", 400)

        newShares = currentShares - sellShares

        if newShares == 0:
            db.execute(
                "DELETE FROM total_stock WHERE user_id = ? AND stock = ?", session["user_id"], symbol
                )
        else:
            db.execute(
                "UPDATE total_stock SET number = ? WHERE user_id = ? AND stock = ?", newShares, session["user_id"], symbol
                )

        stock = lookup(symbol)

        price = stock["price"]

        soldSharesValue = float(price) * sellShares

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", soldSharesValue, session["user_id"]
            )

        db.execute(
            "INSERT INTO purchases (user_id, stock, price, number) VALUES (?, ?, ?, ?)", session["user_id"], symbol, soldSharesValue, -sellShares
            )

        return redirect("/")

    else:
        return render_template("sell.html", allShares=allShares)
