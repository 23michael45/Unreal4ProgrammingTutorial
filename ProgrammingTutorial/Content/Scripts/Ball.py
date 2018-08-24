import unreal_engine as ue		
		
class Ball:

    def begin_play(self):
        self.uobject.enable_input()
        self.uobject.bind_event('OnActorBeginOverlap', self.manage_overlap)
        self.uobject.bind_action('Jump', ue.IE_PRESSED, self.uobject.jump)
        self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K)
        self.uobject.bind_axis('MoveForward', self.move_forward)
    def tick(self, delta_time):
        pass
    def manage_overlap(self, me, other):
        ue.print_string('overlapping ' + other.get_name())
        
    def you_pressed_K(self):
        ue.log_warning('you pressed K')
        
    def move_forward(self, amount):
        ue.print_string('axis value: ' + str(amount))