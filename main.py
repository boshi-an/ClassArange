import ctypes
my_lib = ctypes.cdll.LoadLibrary("./linux/flow.so")

class MinCostFlow(object):
    def __init__(self):
        # Declare input and output types for each method you intend to use
        my_lib.init.argtypes = []
        my_lib.init.restype = ctypes.c_void_p

        my_lib.addeg.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        my_lib.addeg.restype = ctypes.c_void_p

        my_lib.mincost_flow.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
        my_lib.mincost_flow.restype = ctypes.c_int

        my_lib.get_flow_of_edge.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
        my_lib.get_flow_of_edge.restype = ctypes.c_int

        self.obj = my_lib.init()
    
    def add_edge(self, x, y, cap, val) :

        my_lib.addeg(self.obj, x, y, cap, val)
    
    def mincost_flow(self, src, tar) :

        return my_lib.mincost_flow(self.obj, src, tar)
    
    def get_flow_of_edge(self, x, y) :

        return my_lib.get_flow_of_edge(self.obj, x, y)

class ArrangeClass() :

    '''
    student_time_list: <list<list<int>>>, the time list of students, a 0 means have no time, a 1 means have time on that timespot
    teacher_time_list: <list<list<int>>>, the time list of teachers, a 0 means have no time, a 1 means have time on that timespot
    student_value: <list<int>>, the value of each student
    '''
    def __init__(self, student_time_list, teacher_time_list, student_value):

        self.student_num = len(student_time_list)
        self.teacher_num = len(teacher_time_list)
        self.student_time_list = student_time_list
        self.teacher_time_list = teacher_time_list
        self.student_value = student_value
        self.time_num = len(self.student_num[0])
        assert(len(student_value) == self.student_num)
        for student in student_time_list :
            assert(len(student) == self.time_num)
        for teacher in teacher_time_list :
            assert(len(teacher) == self.time_num)
        self.solver = MinCostFlow()     # max edge num is 1e5
        pass

    def compute(self) :

        S = 1
        T = 2
        Stu0 = 3
        Tea0 = Stu0 + self.student_num
        Time0 = Tea0 + self.teacher_num

        for i in range(self.student_num) :
            self.solver.add_edge(S, Stu0 + i, 1, self.student_value[i])
        
        for i in range(self.teacher_num) :
            self.solver.add_edge(Tea0 + i, T, 1, 0)
        
# network = MinCostFlow()
# network.add_edge(1, 2, 3, 4)

# print(network.mincost_flow(1, 2))
# print(network.get_flow_of_edge(1, 2))