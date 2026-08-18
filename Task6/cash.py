from cs50 import get_float

def main():
    # نطلب المبلغ من المستخدم لحد ما يدخل رقم موجب
    while True:
        dollars = get_float("Change owed: ")
        if dollars >= 0:
            break

    # نحول الدولار لـ سنت عشان الحسابات تبقى أرقام صحيحة
    cents = round(dollars * 100)

    # نحسب عدد العملات
    count = 0

    # فئات العملات المتاحة
    coins = [25, 10, 5, 1]

    for coin in coins:
        count += cents // coin  # نشوف الفئة دي فيها كام عملة
        cents %= coin           # نشوف الباقي كام

    print(count)

if __name__ == "__main__":
    main()
