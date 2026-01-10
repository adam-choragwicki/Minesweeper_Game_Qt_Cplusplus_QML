// Mine.qml
import QtQuick

Item {
    id: root
    required property real size
    width: size
    height: size

    // visual proportions
    property real coreRadius: size * 0.30
    property int spikes: 8
    property real spikeLength: size * 0.22
    property real spikeThickness: Math.max(1, size * 0.06)

    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            var w = root.width;
            var h = root.height;
            var cx = w / 2;
            var cy = h / 2;

            ctx.save();
            ctx.translate(cx, cy);

            // draw spikes
            for (var i = 0; i < spikes; ++i) {
                var angle = (Math.PI * 2 * i) / spikes;
                ctx.save();
                ctx.rotate(angle);
                // spike shaft (rounded rectangle)
                ctx.beginPath();
                var sx = coreRadius + 2;
                var sy = -spikeThickness / 2;
                roundRect(ctx, sx, sy, spikeLength, spikeThickness, spikeThickness / 2);
                ctx.fillStyle = "#444444";
                ctx.fill();

                // spike tip (small circle)
                ctx.beginPath();
                ctx.fillStyle = "#2E2E2E";
                ctx.arc(sx + spikeLength + spikeThickness * 0.45, 0, spikeThickness * 0.6, 0, Math.PI * 2);
                ctx.fill();

                ctx.restore();
            }

            // main body: radial gradient for metallic ball
            var bodyRadius = coreRadius;
            var g = ctx.createRadialGradient(0 - bodyRadius * 0.2, 0 - bodyRadius * 0.25, bodyRadius * 0.1, 0, 0, bodyRadius);
            g.addColorStop(0, "#f5f5f5");
            g.addColorStop(0.18, "#cfcfcf");
            g.addColorStop(0.6, "#6b6b6b");
            g.addColorStop(1, "#2c2c2c");
            ctx.beginPath();
            ctx.fillStyle = g;
            ctx.arc(0, 0, bodyRadius, 0, Math.PI * 2);
            ctx.fill();

            // rivet / center bolt
            ctx.beginPath();
            ctx.fillStyle = "#1f1f1f";
            ctx.arc(0, 0, bodyRadius * 0.18, 0, Math.PI * 2);
            ctx.fill();

            // small metallic highlight
            ctx.beginPath();
            ctx.fillStyle = "rgba(255,255,255,0.65)";
            ctx.ellipse(-bodyRadius * 0.28, -bodyRadius * 0.36, bodyRadius * 0.34, bodyRadius * 0.18, 0, 0, Math.PI * 2);
            ctx.fill();

            ctx.restore();

            // helper inside Canvas as well
            function roundRect(ctx, x, y, w, h, r) {
                if (r > w / 2) r = w / 2;
                ctx.beginPath();
                ctx.moveTo(x + r, y);
                ctx.arcTo(x + w, y, x + w, y + h, r);
                ctx.arcTo(x + w, y + h, x, y + h, r);
                ctx.arcTo(x, y + h, x, y, r);
                ctx.arcTo(x, y, x + w, y, r);
                ctx.closePath();
            }
        }
    }
}
