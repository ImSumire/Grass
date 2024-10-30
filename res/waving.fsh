#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float time;
uniform vec2 pos;

out vec4 finalColor;

void main() {
    float attenuation = 1.0 - fragTexCoord.y * fragTexCoord.y;

    float waveFactorX = (
        sin(fragTexCoord.y * 3.0 + time * 3.0 + pos.x - pos.y * 0.618046972) * 0.045 +
        sin(fragTexCoord.y * 3.0 + time * 7.0 + pos.x - pos.y * 0.5) * 0.005
    ) * attenuation;
    float waveFactorY = sin(fragTexCoord.x * 3.0 + time + pos.x - pos.y) * 0.045 * attenuation;

    vec2 uv;
    uv.x = clamp(fragTexCoord.x + waveFactorX, 0.0, 1.0);
    uv.y = clamp(fragTexCoord.y + waveFactorY, 0.0, 1.0);

    vec4 texelColor = texture(texture0, uv);
    finalColor = texelColor * fragColor;
}
