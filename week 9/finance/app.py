import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd
import logging

# Configure application
app = Flask(__name__)

# Custom f)lter
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
    if request.method == "GET":

        try:
            stocks = db.execute(
                f'SELECT * FROM stocks WHERE id == "{session["user_id"]}"'
            )

            cash = db.execute(
                f'SELECT cash FROM users WHERE id == "{session["user_id"]}"'
            )[0]["cash"]

            total = 0

            for stock in stocks:
                total += float(stock["price"]) * float(stock["shares"])
                stock["price"] = stock["price"]

                print(stock["price"])

                stock["total"] = float(stock["price"]) * float(stock["shares"])

                print(stock)

            total = total + cash

            print()

            return render_template("index.html", stocks=stocks, cash=cash, total=total)
        except:
            logging.exception("")
            return apology("index failed")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("There must be a symbol")
        elif not request.form.get("shares"):
            return apology("There must be shares")

        if not is_int(request.form.get("shares")):
            return apology("shares must be an int")

        if int(request.form.get("shares")) < 0:
            return apology("shares must be greater than 0")

        try:
            valid = lookup(request.form.get("symbol"))
            if not valid:
                return apology("invalid symbol")

            user = db.execute(f'SELECT * FROM users WHERE id == {session["user_id"]}')
            if int(user[0]["cash"]) < (float(valid["price"]) * int(request.form.get("shares"))):
                return apology("you cannot afford the stock")

            db.execute(f'UPDATE users SET cash = cash - {float(valid["price"]) * int(
                request.form.get("shares"))} WHERE id == {session["user_id"]}')

            existing_stocks = db.execute(
                f'SELECT * FROM stocks WHERE id == "{session["user_id"]
                                                     }" and symbol == "{valid["symbol"]}"'
            )

            shares = request.form.get("shares")
            id = session["user_id"]
            symbol = valid["symbol"]
            price = valid["price"]
            now = datetime.now()
            formatted_time = now.strftime("%Y-%m-%d %H:%M:%S")

            if not existing_stocks:
                db.execute(
                    f'INSERT INTO stocks (id, symbol, price, time, shares) VALUES ({id}, "{
                        symbol}", {price}, "{formatted_time}", {shares})'
                )
            else:
                db.execute(
                    f'UPDATE stocks SET shares = shares + {int(shares)} WHERE id == "{
                        session["user_id"]}" and symbol == "{valid["symbol"]}"'
                )

            db.execute(
                f'INSERT INTO history (id, shares, time, symbol, price) VALUES ({id}, {
                    shares}, "{formatted_time}", "{symbol}", {price})'
            )

            return redirect("/")

        except:

            return apology("Failed to buy")
    else:
        logging.exception("")
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    if request.method == "GET":
        transactions = db.execute(
            f'SELECT * FROM history WHERE id == {session["user_id"]}'
        )

        return render_template("history.html", transactions=transactions)


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")

        elif not request.form.get("password"):
            return apology("must provide username")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match")

        try:
            hash = generate_password_hash(request.form.get("password"))
            username = request.form.get("username")

            rows = db.execute(f'SELECT * FROM users WHERE username == "{username}"')

            if len(rows) >= 1:
                return apology("That username is already taken")

            db.execute(
                f'INSERT INTO users (username, hash) VALUES ("{username}", "{hash}")'
            )

            userquery = db.execute(
                f'SELECT id FROM users WHERE username == "{username}"'
            )

            session["user_id"] = userquery[0]["id"]

            return redirect("/")
        except:
            return apology("register failed")
    else:
        return render_template("register.html")


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


@app.route("/reset", methods=["GET", "POST"])
def reset():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")

        elif not request.form.get("password"):
            return apology("must provide username")

        try:
            username = request.form.get("username")
            hash = generate_password_hash(request.form.get("password"))

            user = db.execute(f'SELECT * FROM users WHERE username == "{username}"')
            if len(user) < 1:
                return apology("Invalid username")
            else:
                db.execute(
                    f'UPDATE users SET hash = "{hash}" WHERE username == "{username}"'
                )
            return redirect("/login")
        except:
            logging.exception("")
            return apology("Failed to reset your password")
    else:
        return render_template("reset.html")


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
    if request.method == "POST":
        try:
            symbol = lookup(request.form.get("symbol"))
            print(symbol)
            if not symbol:
                return apology("Invalid Symbol")
            else:
                return render_template(
                    "quote.html",
                    price=f'{usd(symbol["price"])}", symbol=f"{symbol["symbol"]}',
                )

        except:
            return apology("Quote failed")

    else:
        return render_template("quoteform.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        try:
            stocks = db.execute(
                f'SELECT * FROM stocks WHERE id == "{session["user_id"]}"'
            )
            return render_template("sell.html", stocks=stocks)
        except:
            return apology("selling failed")
    else:
        if not request.form.get("symbol"):
            return apology("No symbol.")
        elif not request.form.get("shares"):
            return apology("No shares.")

        try:
            stock = lookup(request.form.get("symbol"))
            shares = int(request.form.get("shares"))

            price = float(stock["price"]) * shares

            db.execute(
                f'UPDATE users SET cash == cash + {price} WHERE id == "{session["user_id"]}"'
            )
            findstock = db.execute(
                f'SELECT * FROM stocks WHERE id == "{session["user_id"]
                                                     }" AND symbol == "{stock["symbol"]}"'
            )

            if int(findstock[0]["shares"]) > shares:
                db.execute(
                    f'UPDATE stocks SET shares = shares - {int(shares)} WHERE id == "{
                        session["user_id"]}" AND symbol == "{stock["symbol"]}"'
                )
            elif int(findstock[0]["shares"]) == shares:
                db.execute(
                    f'DELETE FROM stocks WHERE id == "{
                        session["user_id"]}" AND symbol == "{stock["symbol"]}"'
                )
            else:
                return apology("not enough shares")

            now = datetime.now()
            formatted_time = now.strftime("%Y-%m-%d %H:%M:%S")

            db.execute(
                f'INSERT INTO history (id, shares, time, symbol, price) VALUES ({
                    session["user_id"]}, -{shares}, "{formatted_time}", "{stock["symbol"]}", {stock["price"]})'
            )

            return redirect("/")

        except:

            return apology("selling failed")


def is_int(s):

    try:
        int(s)
        return True
    except ValueError:
        return False
