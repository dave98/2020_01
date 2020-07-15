class lexema:
    def __init__(self, _type="", _description=""):
        self.l_type = _type
        self.l_description = _description

    def first(self):
        return self.l_type

    def second(self):
        return self.l_description

    def __str__(self):
        return "<" + self.l_type + ":" + self.l_description + ">"

    def to_print(self):
        if self.l_description != "":
            return self.l_description
        else:
            return self.l_type
