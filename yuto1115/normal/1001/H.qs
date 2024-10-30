namespace Solution {
    open Microsoft.Quantum.Canon;
    open Microsoft.Quantum.Intrinsic;
    open Microsoft.Quantum.Convert;

    operation Solve (x : Qubit[], y : Qubit) : Unit {
        for(i in 0 .. Length(x)-1) {
            CNOT(x[i],y);
        }
    }
}