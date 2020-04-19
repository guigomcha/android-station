import serial

commands = {'ON': '1', 'OFF': '0'}
com_conf = {'name': 'COM9', 'baud': 9600}

if __name__ == '__main__':
    """
    In order to use this functionality you will need to first pair the device where this code is executed to the
    receiver. In my case: HC-06 with default password.
    """
    s = serial.Serial(com_conf['name'], com_conf['baud'], timeout=2)
    s.write(bytes(commands['ON'], 'utf-8'))