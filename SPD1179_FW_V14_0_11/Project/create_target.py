import re
import shutil
import os


INDEPENDENT_PROJECT = '23_1_Predriver_Operation'


if __name__ == '__main__':
    current_path = os.getcwd()
    x = input('Enter 0 or 1, means in 0_Examples or 1_Application\n')
    if x == '0':
        y = input('Input project name\n')
        searchObject = re.search(r'\s', y)
        if searchObject:
            print('The input is illegal, contain space')
            exit(1)
        target = current_path + '\\0_Examples\\' + y
        z = input('Enter d or i, means dependent or independent\n')
        if z == 'd':
            source = current_path + '\\0_Examples\\Template'
        elif z == 'i':
            source = current_path + '\\0_Examples\\' + INDEPENDENT_PROJECT
        else:
            print('The input is illegal')
            exit(1)
        print('Copy from {} to {}'.format(source, target))
        shutil.copytree(source, target)
    elif x == '1':
        y = input('Input project name\n')
        searchObject = re.search(r'\s', y)
        if searchObject:
            print('The input is illegal, contain space')
            exit(1)
        target = current_path + '\\1_Application\\' + y
        z = input('Enter d or i, means dependent or independent\n')
        if z == 'd':
            source = current_path + '\\0_Examples\\Template'
        elif z == 'i':
            source = current_path + '\\0_Examples\\' + INDEPENDENT_PROJECT
        else:
            print('The input is illegal')
            exit(1)
        print('Copy from {} to {}'.format(source, target))
        shutil.copytree(source, target)
    else:
        print('no operation')

    os.system('pause')