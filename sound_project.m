device = serialport("COM6",9600);
configureTerminator(device,"CR/LF");
flush(device);

songs = ["d:\e\ap\mambo_no_5-lou_bega.wav",
        "d:\e\ap\dont_speak-no_doubt.wav",
        "d:\e\ap\i_ran_so_far_away-flock_of_seagulls.wav",
        "d:\e\ap\around_the_world-atc.wav",
        "d:\e\ap\africa-toto.wav"
        ];
i = 1;
PO = getMusic(songs(i));

message = readline(device)
if isempty(message)
    message = "play"
end
while message~="stop"
    if message=="play"
        % Play audio
        play(PO)
    elseif message=="next" 
        if i<length(songs)
            i = i+1;
            PO = getMusic(i)
            play(PO)
        end
    elseif message=="prev" 
        if i>0
            i = i-1;
            PO = getMusic(i)
            play(PO)
        end
    end
    message = readline(device)
    if isempty(message)
        message = "none"
    end
end
% Stop audio
stop(PO)

function music = getMusic(filename)
    [y,Fs] = audioread(filename);
    music = audioplayer(y,Fs);
end
