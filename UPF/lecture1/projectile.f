      program projectile
c     simple program computing a projectile trajectory

c     nothing implicit, must declare everything
      implicit none

c     declare variables
      integer          max_n
      parameter        (max_n=10000)             ! array size
      double precision PI
      parameter        (PI=3.14159265358979d0)   ! pi constant
      double precision height,vel,angle,m        ! gun parameters
      double precision k,gravity,dt              ! air resistence, gravity, timestep
      double precision time(0:max_n)             ! sequence of times
      double precision x(0:max_n),y(0:max_n)     ! projectile position
      double precision u(0:max_n),v(0:max_n)     ! projectile velocities
      integer          n_step,i                  ! loop counters
      integer          is_running                ! flag whether to run or stop

c     set initial parameters
      height =  0.0d0           ! height of the gun above the ground
      vel    = 44.7d0           ! initial shoot velocity
      angle  = PI/4.0d0         ! angle of the gun
      m      = 0.145d0          ! projectile mass
      gravity= -9.81d0          ! gravity constant
      dt     = 0.01d0           ! time step
      k      = 0.0431d0         ! air resistence
     
c     initialize the intial projectile quantities
      x(0) = 0.0d0              ! positions
      y(0) = height
      u(0) = vel*cos(angle)     ! velocities
      v(0) = vel*sin(angle)
      time(0) = 0.0d0           ! initial time moment

c     main program loop
      is_running = 1
      n_step = 0
      do while (is_running.gt.0)
c     increate step counter
         n_step = n_step + 1
         if (n_step.gt.max_n) then
            write(*,*) 'Timestep number too big'
            write(*,*) 'n_step = ',n_step,', max_n = ',max_n
            write(*,*) 'Increase max_n and recompile'
            stop
         endif
         time(n_step) = time(n_step-1) + dt

c     perform timestep - update positions and velocities
         u(n_step) = u(n_step-1)                - k*u(n_step-1)/m*dt
         v(n_step) = v(n_step-1) + gravity*dt   - k*v(n_step-1)/m*dt
         x(n_step) = x(n_step-1) + u(n_step)*dt
         y(n_step) = y(n_step-1) + v(n_step)*dt

         if (y(n_step).le.0.0d0) then
c     impact to the ground -> stop the simulation
            is_running = 0
         endif

      enddo

c     output everything to a file
      open(10,file='output',status='replace')
      do i=0,n_step
         write(10,100) i,time(i),x(i),y(i),u(i),v(i)
      enddo
      close(10)
 100  format(i5,5e23.15)

      end
