function A=Ajacob1(x,dt,v_,str_angle)
    A=zeros(6,6);
    beta_=x(2);
    yaw_=x(4);

    A(3,1)=(10*cos(beta_)*tan(str_angle))/27;
    A(3,2)=-1*(10*v_*sin(beta_)*tan(str_angle))/27;
    A(4,3)=dt;
    A(4,4)=1;
    A(5,1)=dt*cos(beta_+yaw_);
A(5,2)=-1*dt*v_*sin(beta_+yaw_);
    A(5,4)=-1*dt*v_*sin(beta_+yaw_);
    A(5,5)=1;
    A(6,1)=dt*sin(beta_+yaw_);
    A(6,2)=dt*v_*cos(beta_+yaw_);
    A(6,4)=dt*v_*cos(beta_+yaw_);
	A(6,6)=1;
end