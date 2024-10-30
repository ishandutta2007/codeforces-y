/+ dub.sdl:
    name "A"
    dependency "dcomp" version=">=0.9.0"
+/

import std.stdio, std.algorithm, std.range, std.conv;
// import dcomp.foundation, dcomp.scanner;

import std.typecons;

int main() {
    Scanner sc = new Scanner(stdin);

    int h; int[] a;
    sc.read(h, a); h++;
    int[] as = new int[h+1];
    foreach (i; 0..h) {
        as[i+1] = as[i] + a[i];
    }
    int n = as.back;
    int[] ap = new int[n], bp = new int[n];
    ap[0] = -1; bp[0] = -1;
    foreach (i; 1..h) {
        foreach (j; as[i]..as[i+1]) {
            ap[j] = bp[j] = as[i-1];
        }
    }
    foreach (i; 0..h-1) {
        if (a[i] > 1 && a[i+1] > 1) {
            bp[as[i+1]+1]++;

            writeln("ambiguous");
            writeln(ap.map!"a+1".map!(to!string).join(" "));
            writeln(bp.map!"a+1".map!(to!string).join(" "));
            return 0;
        }
    }
    writeln("perfect");
    return 0;
}
/* IMPORT /home/yosupo/Program/dcomp/source/dcomp/foundation.d */
 
// module dcomp.foundation;

 
static if (__VERSION__ <= 2070) {
    /*
    Copied by https://github.com/dlang/phobos/blob/master/std/algorithm/iteration.d
    Copyright: Andrei Alexandrescu 2008-.
    License: $(HTTP boost.org/LICENSE_1_0.txt, Boost License 1.0).
    */
    template fold(fun...) if (fun.length >= 1) {
        auto fold(R, S...)(R r, S seed) {
            import std.algorithm : reduce;
            static if (S.length < 2) {
                return reduce!fun(seed, r);
            } else {
                import std.typecons : tuple;
                return reduce!fun(tuple(seed), r);
            }
        }
    }
     
}
/* IMPORT /home/yosupo/Program/dcomp/source/dcomp/scanner.d */
// module dcomp.scanner;

// import dcomp.container.stackpayload;

 
class Scanner {
    import std.stdio : File;
    import std.conv : to;
    import std.range : front, popFront, array, ElementType;
    import std.array : split;
    import std.traits : isSomeChar, isStaticArray, isArray; 
    import std.algorithm : map;
    File f;
    this(File f) {
        this.f = f;
    }
    char[512] lineBuf;
    char[] line;
    private bool succW() {
        import std.range.primitives : empty, front, popFront;
        import std.ascii : isWhite;
        while (!line.empty && line.front.isWhite) {
            line.popFront;
        }
        return !line.empty;
    }
    private bool succ() {
        import std.range.primitives : empty, front, popFront;
        import std.ascii : isWhite;
        while (true) {
            while (!line.empty && line.front.isWhite) {
                line.popFront;
            }
            if (!line.empty) break;
            line = lineBuf[];
            f.readln(line);
            if (!line.length) return false;
        }
        return true;
    }

    private bool readSingle(T)(ref T x) {
        import std.algorithm : findSplitBefore;
        import std.string : strip;
        import std.conv : parse;
        if (!succ()) return false;
        static if (isArray!T) {
            alias E = ElementType!T;
            static if (isSomeChar!E) {
                 
                 
                auto r = line.findSplitBefore(" ");
                x = r[0].strip.dup;
                line = r[1];
            } else static if (isStaticArray!T) {
                foreach (i; 0..T.length) {
                    bool f = succW();
                    assert(f);
                    x[i] = line.parse!E;
                }
            } else {
                StackPayload!E buf;
                while (succW()) {
                    buf ~= line.parse!E;
                }
                x = buf.data;
            }
        } else {
            x = line.parse!T;
        }
        return true;
    }
    int read(T, Args...)(ref T x, auto ref Args args) {
        if (!readSingle(x)) return 0;
        static if (args.length == 0) {
            return 1;
        } else {
            return 1 + read(args);
        }
    }
}


 
 

 
/* IMPORT /home/yosupo/Program/dcomp/source/dcomp/container/stackpayload.d */
// module dcomp.container.stackpayload;

 
struct StackPayload(T, size_t MINCAP = 4) if (MINCAP >= 1) {
    import core.exception : RangeError;

    private T* _data;
    private uint len, cap;

    @property bool empty() const { return len == 0; }
    @property size_t length() const { return len; }
    alias opDollar = length;

     
    inout(T)[] data() inout { return (_data) ? _data[0..len] : null; }
    
    ref inout(T) opIndex(size_t i) inout {
        version(assert) if (len <= i) throw new RangeError();
        return _data[i];
    }  
    ref inout(T) front() inout { return this[0]; }  
    ref inout(T) back() inout { return this[$-1]; }  

    void reserve(size_t newCap) {
        import core.memory : GC;
        import core.stdc.string : memcpy;
        import std.conv : to;
        if (newCap <= cap) return;
        void* newData = GC.malloc(newCap * T.sizeof);
        cap = newCap.to!uint;
        if (len) memcpy(newData, _data, len * T.sizeof);
        _data = cast(T*)(newData);
    }  
    void free() {
        import core.memory : GC;
        GC.free(_data);
    }  
     
    void clear() {
        len = 0;
    }

    void insertBack(T item) {
        import std.algorithm : max;
        if (len == cap) reserve(max(cap * 2, MINCAP));
        _data[len++] = item;
    }  
    alias opOpAssign(string op : "~") = insertBack;  
    void removeBack() {
        assert(!empty, "StackPayload.removeBack: Stack is empty");
        len--;
    }  
}

 

/*
This source code generated by dcomp and include dcomp's source code.
dcomp's Copyright: Copyright (c) 2016- Kohei Morita. (https://github.com/yosupo06/dcomp)
dcomp's License: MIT License(https://github.com/yosupo06/dcomp/blob/master/LICENSE.txt)
*/