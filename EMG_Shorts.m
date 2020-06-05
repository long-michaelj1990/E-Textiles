%%%Connect to arduino
a=arduino ();
configurePin(a,'D12','DigitalOutput');

t = 0 ;
x = 0 ;
startSpot = 0;
interv = 1000 ; % considering 1000 samples
step = 0.1 ; % lowering step has a number of cycles and then acquire more data

while ( t <interv )
    EMG=readVoltage(a,'A0');
    x = [ x, EMG ];
    plot(x) ;
if EMG>=2
   writeDigitalPin(a,'D12',1);
elseif EMG<2
        writeDigitalPin(a,'D12',0); 
end
    
      if ((t/step)-500 < 0)
          startSpot = 0;
      else
          startSpot = (t/step)-500;
      end
      axis([ startSpot, (t/step+50), 0 , 10 ]);
      grid
      t = t + step;
      drawnow;
      pause(0.01)
end
