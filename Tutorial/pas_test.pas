BEGIN
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number / 4;
        c := a - b;
	d := 30;
    END;
    x := 11;
END.