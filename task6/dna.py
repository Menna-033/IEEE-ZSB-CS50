import csv
import sys

def main():
    # التحقق من المدخلات
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # 1. قراءة قاعدة البيانات
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        fieldnames = reader.fieldnames[1:] # دي الـ STRs زي AGATC, إلخ
        for row in reader:
            database.append(row)

    # 2. قراءة ملف الـ DNA
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # 3. حساب أطول تكرار لكل STR في قاعدة البيانات
    counts = {}
    for str_type in fieldnames:
        counts[str_type] = longest_match(sequence, str_type)

    # 4. مقارنة النتائج بقاعدة البيانات
    for person in database:
        match = True
        for str_type in fieldnames:
            if int(person[str_type]) != counts[str_type]:
                match = False
                break
        if match:
            print(person["name"])
            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)
    return longest_run

if __name__ == "__main__":
    main()
