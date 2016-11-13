class MasterSlaveCommand:

    # Defined State of slave
    #
    # TRAN: transfer
    # IDLE: @ this is a default state if slave doesn's receive any cmd
    # IRRI: irrigation
    # TEST: test
    # SENS: sense
    #
    states = ['TRAN','IRRI','SENS']

    # Defined commands between master and slave
    # Abbreviated command name and format
    #
    # TRAN: source, dest, method
    # IDLE:
    # IRRI: IRRI, actucatorPin, executingTime
    # TEST: @ this command should be implementated by firmata library
    # SENS: SENS, sensorPin
    #
    cmds = ['TRAN','IRRI','SENS']

    def __init__(self):
        print("constructed!")

    def get_all_states(self):
        return self.states

    def get_all_commands(self):
        return self.cmds

    def get_CMD_TRAN(self, source, dest, method):
        return "TRAN,{},{},{}".format(source, dest, method)

    def get_CMD_IRRI(self, actucatorPin, executingTime, restTime):
        return "IRRI,{},{},{}".format(actucatorPin, executingTime, restTime)

    def get_CMD_SENS(self, sensorPin):
        return "SENS,{}".format(sensorPin)
