#[link(name = "sample_clib", kind = "static")]
unsafe extern "C" {
    pub fn get_libtype() -> u8;

    pub fn sum_of_least_two(val_a: u16, val_b: u16, val_c: u16) -> u32;
}
