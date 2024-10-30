namespace Solution {

    open Microsoft.Quantum.Arithmetic;
    open Microsoft.Quantum.Canon;
    open Microsoft.Quantum.Convert;
    open Microsoft.Quantum.Diagnostics;
    open Microsoft.Quantum.Intrinsic;
    open Microsoft.Quantum.Math;

    operation A5(unitary: (Qubit => Unit is Adj+Ctl)) : Int {
        body(...) {
            using(qs=Qubit[2]) {
                let q=qs[0];
                let r=qs[1];
                H(q);
                CNOT(q,r);
                (Controlled unitary)([q],r);
                CZ(q,r);
                CNOT(q,r);
                H(q);
                if (M(q)==One) {
                    ResetAll(qs);
                    return 1;
                } else {
                    ResetAll(qs);
                    return 0;
                }
            }
        }
    }

    operation SWP(x: Qubit, y: Qubit) : Unit is Adj+Ctl {
        body (...) {
            CNOT(x,y);
            CNOT(y,x);
            CNOT(x,y);
        }
    }
    operation GenW3(qs: Qubit[]) : Unit {
        body (...) {
            using(rs = Qubit[4]) {
                repeat {
                    X(rs[0]);
                    using(z = Qubit()) {
                        H(z);
                        (Controlled SWP)([z],(rs[0],rs[1]));
                        CNOT(rs[1],z);
                        H(z);
                        (Controlled SWP)([z],(rs[0],rs[2]));
                        (Controlled SWP)([z],(rs[1],rs[3]));
                        CNOT(rs[2],z);
                        CNOT(rs[3],z);
                    }
                } until (M(rs[3]) == Zero) fixup {
                    X(rs[3]);
                }
                SWP(rs[0],qs[0]);
                SWP(rs[1],qs[1]);
                SWP(rs[2],qs[2]);
            }
        }
    }
    operation ProbC(qs:Qubit[]) : Unit {
        body(...) {
            using(rs=Qubit[3]) {
                GenW3(rs);
                SWP(rs[1],qs[0]);
                SWP(rs[2],qs[1]);
                CNOT(rs[0],qs[0]);
                CNOT(rs[0],qs[1]);
                CCNOT(qs[0],qs[1],rs[0]);
            }
        }
    }


    operation Incr(register:LittleEndian) : Unit is Adj+Ctl {
        body(...) {
            let qs=register!;
            if(Length(qs)>0) {
                (Controlled Incr)([qs[0]],LittleEndian(qs[1..Length(qs)-1]));
                X(qs[0]);
            }
        }
    }
    operation Decr(register:LittleEndian) : Unit is Adj+Ctl {
        body(...) {
            (Adjoint Incr)(register);
        }
    }

    operation Solveq(unitary: (Qubit=>Unit is Adj+Ctl)) : Int {
        body(...) {
            using(qs=Qubit[2]) {
                let q=qs[0];
                let r=qs[1];
                H(q);
                CNOT(q,r);
                (Controlled unitary)([q],r);
                // H(q);
                DumpMachine(());
                ResetAll(qs);
                return -1;
            }
        }
    }

    operation INC(qs: Qubit[]) : Unit is Adj+Ctl { body(...) {
        using(d=Qubit()) {
            let a=qs[0];
            let b=qs[1];
            let c=qs[2];
            SWAP(c,d);
            SWAP(b,c);
            SWAP(a,b);
            SWAP(a,d);
        }
        }}

    operation SolveXZvsY(unitary: (Qubit=>Unit is Adj+Ctl)) : Int {
        body(...) {
            using(qs=Qubit[2]) {
                let q=qs[0];
                let r=qs[1];
                H(q);
                CNOT(q,r);
                (Controlled unitary)([q],r);
                (Controlled unitary)([q],r);
                CNOT(q,r);
                H(q);
                mutable z=0;
                if(M(q)==One) { X(q); set z=z+1; }
                H(q);
                CNOT(q,r);
                (Controlled unitary)([q],r);
                if(z==0) { S(q); }
                H(q);
                if(M(q)==One) { X(q); set z=z+2; }
                return z;
            }
        }
    }

    operation Solve7(unitary: (Qubit=>Unit is Adj+Ctl)) : Int {
        body(...) {
            using(qs=Qubit[2]) {
                let q=qs[0];
                let r=qs[1];
                H(q);
                CNOT(q,r);
                unitary(r);
                CNOT(q,r);
                mutable z=0;
                if(M(r)==One) {
                    X(r);
                    set z=3;
                }
                H(q);
                // DumpMachine(());
                if(M(q)==One) {
                    X(q);
                    if(z==0) { set z=1; }
                    else { set z=2; }
                }
                if(z==3) { set z=1; }
                elif(z==1) { set z=3; }
                return z;
            }
        }
    }

    operation Prep(rs: LittleEndian, q: Qubit, r: Qubit) : Unit is Adj+Ctl {
        body(...) {
            H(q);
            H(r);
            (Controlled QFTLE)([q],rs);
            (Controlled QFTLE)([r],rs);
            (Controlled QFTLE)([r],rs);
            (Adjoint QFTLE)(LittleEndian([q,r]));
            // H(r);
            // (Controlled Adjoint S)([r],q);
            // H(q);
            // SWAP(q,r);
        }
    }
    operation Solve(p: Int, inputRegister: LittleEndian) : Unit is Adj+Ctl {
        body(...) {
            using(qs=Qubit[2]) {
                let rs=inputRegister;
                let q=qs[0];
                let r=qs[1];
                Prep(rs,q,r);
                Rz(PI()/2./IntAsDouble(p),q);
                Rz(PI()/IntAsDouble(p),r);
                (Adjoint Prep)(rs,q,r);
            }
        }
    }



    operation neg(q: Qubit) : Unit is Adj+Ctl {
        body(...) {
            Z(q);
            X(q);
            Z(q);
            X(q);
        }
    }
    operation opXZvsY(i: Int, q: Qubit) : Unit is Adj+Ctl { body(...) {
        if(i==0) { Y(q); }
        if(i==1) { Z(q); X(q); neg(q); }
        if(i==2) { Y(q); neg(q); }
        if(i==3) { Z(q); X(q); }
        }}
    operation Tester() : Unit {
        body(...) {
            // Message("qqz");
            // for(i in 0..3) {
            //     Message($"{i}: {Solve(op(i,_))}");
            // }

            let p=8;
            using(qs=Qubit[3]) {
                let rs=LittleEndian(qs);
                for(i in 0..7) {
                    for(j in 1..p) { Solve(p,rs); }
                    (Adjoint QFTLE)(rs);
                    DumpMachine(());
                    Incr(rs);
                }
            }
            // for(i in 0..7) {
            // Message($"0 I {Solve(I)}");
            // Message($"1 X {Solve(X)}");
            // Message($"2 Y {Solve(Y)}");
            // Message($"3 Z {Solve(Z)}");
            // }
            // for(i in 1..4) {
            //     // Message($"{Solve(ApplyPauli([PauliI,PauliX],_))} - {Solve(ApplyToFirstTwoQubitsCA(CNOT,_))}");
            //     Message($"{A5(Z)} - {A5(mZ)}");
            // }
            // using(qs=Qubit[3]) {
            //     for(i in 1..8) {
            //         Decr(LittleEndian(qs));
            //         DumpMachine(());
            //     }
            // }
        }
    }

    operation Main() : Unit {
        body(...) {
            Tester();
        }
    }
}