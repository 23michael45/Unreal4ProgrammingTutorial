import unreal_engine as ue
class PlayerComponent:
    
    def begin_play(self):
        # get a reference to the owing pawn (a character)
        self.pawn = self.uobject.get_owner()
        self.pawn.enable_input()

        # the following two values were originally implemented as blueprint variable
        self.base_turn_rate = 45.0
        self.base_look_up_rate = 45.0

        # bind axis events
        #self.pawn.bind_axis('TurnRate', self.turn)
        #self.pawn.bind_axis('LookUpRate', self.look_up)
        self.pawn.bind_axis('Turn', self.pawn.add_controller_yaw_input)
        self.pawn.bind_axis('LookUp', self.pawn.add_controller_pitch_input)

        self.pawn.bind_axis('MoveForward', self.move_forward)
        self.pawn.bind_axis('MoveRight', self.move_right)

        # bind actions
        self.pawn.bind_action('Jump', ue.IE_PRESSED, self.pawn.jump)
        self.pawn.bind_action('Jump', ue.IE_RELEASED, self.pawn.stop_jumping)

    def turn(self, axis_value):
        turn_rate = axis_value * self.base_turn_rate * self.uobject.get_world_delta_seconds()
        self.pawn.add_controller_yaw_input(turn_rate)

    def look_up(self, axis_value):
        look_up_rate = axis_value * self.base_look_up_rate * self.uobject.get_world_delta_seconds()
        self.pawn.add_controller_pitch_input(look_up_rate)

    def move_forward(self, axis_value):
        rot = self.pawn.get_control_rotation()
        fwd = ue.get_forward_vector(0, 0, rot[2])
        self.pawn.add_movement_input(fwd, axis_value)

    def move_right(self, axis_value):
        rot = self.pawn.get_control_rotation()
        right = ue.get_right_vector(0, 0, rot[2])
        self.pawn.add_movement_input(right, axis_value)