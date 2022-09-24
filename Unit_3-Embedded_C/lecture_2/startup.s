@ reset section and make it global ,hence the other files can see it

.global reset
reset:              
    ldr sp, = stak_top

    @branch to the main function
    bl main

@stop section and branch itself 
stop: b stop