function formatDate(self, rawValue)
{
    if (rawValue == null)
    {
        return null;
    }

    return new Date(rawValue * 1000).toLocaleDateString();
}

function percentValue(self, rawValue)
{
    if (rawValue == null)
    {
        return null;
    }

    return rawValue.toFixed(2) + "%";
}

function getSize()
{
    // mobile layout
    let newWidth = window.innerWidth - 0.06 * window.innerWidth;
    let newHeight = newWidth / 2;

    // min height
    if (newHeight < 300)
    {
        newHeight = 300;
    }

    // full layout
    if (window.innerWidth >= 900)
    {
        newWidth = 730;
        newHeight = 370;
    }

    return {
        width: newWidth,
        height: newHeight,
    }
}

let codeOpts =
{
    ...getSize(),
    series:
    [
        {
            label: "Date",
            value: formatDate,
        },
        {
            label: "Total",
            scale: "%",
            width: 3,
            stroke: "rgb(85, 191, 59)",
            value: percentValue,
        },
        {
            show: false,
            label: "Boot",
            scale: "%",
            width: 3,
            stroke: "rgb(255, 99, 132)",
            value: percentValue,
        },
        {
            show: false,
            label: "Code",
            scale: "%",
            width: 3,
            stroke: "rgb(82, 146, 252)",
            value: percentValue,
        },
        {
            show: false,
            label: "Overlays",
            scale: "%",
            width: 3,
            stroke: "rgb(227, 172, 52)",
            value: percentValue,
        },
    ],
    axes:
    [
        {
            grid: {show: false},
        },
        {
            scale: "%",
            incrs: [25,],
            values: (self, ticks) => ticks.map(rawValue => rawValue.toFixed(0) + "%"),
            grid:
            {
                stroke: "rgb(182, 235, 253)",
                width: 3,
            },
        },
    ],
    scales:
    {
        "%":
        {
            auto: true,
            range: [0, 100],
        }
    },
};

let assetOpts =
{
    ...getSize(),
    series:
    [
        {
            label: "Date",
            value: formatDate,
        },
        {
            label: "Total",
            scale: "%",
            width: 3,
            stroke: "rgb(85, 191, 59)",
            value: percentValue,
        },
        {
            show: false,
            label: "Objects",
            scale: "%",
            width: 3,
            stroke: "rgb(255, 99, 132)",
            value: percentValue,
        },
    ],
    axes:
    [
        {
            grid: {show: false},
        },
        {
            scale: "%",
            incrs: [25,],
            values: (self, ticks) => ticks.map(rawValue => rawValue.toFixed(0) + "%"),
            grid:
            {
                stroke: "rgb(182, 235, 253)",
                width: 3,
            },
        },
    ],
    scales:
    {
        "%":
        {
            auto: true,
            range: [0, 100],
        }
    },
};

let codeGraph = new uPlot(codeOpts, null, document.getElementById("codeGraph"));
let assetGraph = new uPlot(assetOpts, null, document.getElementById("assetGraph"));

fetch('https://progress.decomp.club/data/animalforest/jp/?mode=all')
.then(v => v.json())
.then(result =>
{
    const codeProgress = result['animalforest']['jp']['code'][0]['measures'];
    document.getElementById("codeProgressTotal").innerHTML = (100 * codeProgress['all'] / codeProgress['all/total']).toFixed(2) + "%";
    document.getElementById("codeProgressBoot").innerHTML = (100 * codeProgress['boot'] / codeProgress['boot/total']).toFixed(2) + "%";
    document.getElementById("codeProgressCode").innerHTML = (100 * codeProgress['code'] / codeProgress['code/total']).toFixed(2) + "%";
    document.getElementById("codeProgressOverlays").innerHTML = (100 * codeProgress['overlays'] / codeProgress['overlays/total']).toFixed(2) + "%";

    const codeEntries = result['animalforest']['jp']['code'].reverse();
    codeGraph.setData([
        codeEntries.map(a => a.timestamp),
        codeEntries.map(a => 100 * (a.measures['all'] / a.measures['all/total'])),
        codeEntries.map(a => 100 * (a.measures['boot'] / a.measures['boot/total'])),
        codeEntries.map(a => 100 * (a.measures['code'] / a.measures['code/total'])),
        codeEntries.map(a => 100 * (a.measures['overlays'] / a.measures['overlays/total'])),
    ]);

    const assetProgress = result['animalforest']['jp']['assets'][0]['measures'];
    document.getElementById("assetProgressTotal").innerHTML = (100 * assetProgress['all'] / assetProgress['all/total']).toFixed(2) + "%";
    document.getElementById("assetProgressObjects").innerHTML = (100 * assetProgress['objects'] / assetProgress['objects/total']).toFixed(2) + "%";
    
    const assetEntries = result['animalforest']['jp']['assets'].reverse();
    assetGraph.setData([
    assetEntries.map(a => a.timestamp),
    assetEntries.map(a => 100 * (a.measures['all'] / a.measures['all/total'])),
    assetEntries.map(a => 100 * (a.measures['objects'] / a.measures['objects/total'])),
    ]);
});

function throttle(cb, limit)
{
    var wait = false;

    return () =>
    {
        if (!wait)
        {
            requestAnimationFrame(cb);
            wait = true;
            setTimeout(() =>
            {
                wait = false;
            }, limit);
        }
    }
}

window.addEventListener("resize", throttle(() => codeGraph.setSize(getSize()), 100));
window.addEventListener("resize", throttle(() => assetGraph.setSize(getSize()), 100));
