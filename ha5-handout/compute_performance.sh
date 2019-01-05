# Helper script to compute the estimated cycles of valgrind trace. Too lazy
# to write this in python at the moment.  Supply cachegrind trace file
# listing as argument

VALG="valgrind --D1=32768,8,64 --quiet --tool=cachegrind"

function simulate_perf()
{
    local pre=""
    if [[ -f $(pwd)/$1 ]]; then
        pre='./'
    fi
    $VALG --cachegrind-out-file=${1}.trace $pre$1 1>/dev/null
}

function compute_cest()
{
    local file=${1}.trace
    local perf=()
    local instr=0
    local d1mr=0

    if [[ ! -f $file ]]; then
        return
    fi

    #Summary: Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
    perf=($(tail -n1 $file))
    instr=${perf[1]}
    d1mr=${perf[5]}

    # Overall performance is aggregate estimated cycles
    # There are no main memory misses (DLmr) so they are omitted
    echo $(((instr) + 10 * (d1mr)))
}

for f in $@; do
    simulate_perf $f
    perf=$(compute_cest $f)
    echo "$perf $f"
done | sort -n
