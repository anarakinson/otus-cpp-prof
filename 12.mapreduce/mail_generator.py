import random
import string



def random_char(char_num):
       return ''.join(random.choice(string.ascii_letters) for _ in range(char_num))


def make_data(count):

    output = []
    suffixes = ["@gmail.com", "@mail.com", "@mail.ru", "@ya.ru", "@somemail.com"]

    for _ in range(count):
        suffix = suffixes[random.randint(0, len(suffixes) - 1)]
        x = random_char(random.randint(4, 15)).lower() + suffix
        if x not in output:
            output.append(x)

    return output


def write_file(filename, mails):
    with open(filename, "w") as f:
        for mail in mails:
            f.write(mail + "\n")



if __name__ == "__main__":
    mails = make_data(5000)
    write_file("dummy_data.txt", mails)
