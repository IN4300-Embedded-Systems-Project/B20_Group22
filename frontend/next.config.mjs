/** @type {import('next').NextConfig} */
const nextConfig = {
  distDir: "./dist",
  typescript: {
    ignoreBuildErrors: true,
  },
  eslint: {
    ignoreDuringBuilds: true,
  },
};

export default nextConfig;
