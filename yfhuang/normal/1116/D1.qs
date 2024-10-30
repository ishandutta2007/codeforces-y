namespace Solution
{
    open Microsoft.Quantum.Canon;
    open Microsoft.Quantum.Primitive;

    operation C1 (x : Qubit[], y : Qubit) : Unit {
        body(...){
            let N = Length(x);
            for(i in 1..2..N-1){
                X(x[i]);
            }
            Controlled X(x, y);
            for(i in 0..N-1){
                X(x[i]);
            }
            Controlled X(x, y);
            for(i in 0..2..N-1){
                X(x[i]);
            }
        }
        adjoint auto;
    }
    operation Solve (qs : Qubit[]) : Unit {
        H(qs[0]);
    }
}