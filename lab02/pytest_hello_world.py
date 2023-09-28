# # SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
# # SPDX-License-Identifier: CC0-1.0
# 
# import hashlib
# import logging
# from typing import Callable
# 
# import pytest
# from pytest_embedded_idf.dut import IdfDut
# from pytest_embedded_qemu.app import QemuApp
# from pytest_embedded_qemu.dut import QemuDut
# 
# 
# @pytest.mark.supported_targets
# @pytest.mark.preview_targets
# @pytest.mark.generic
# def test_hello_world(
#     dut: IdfDut, log_minimum_free_heap_size: Callable[..., None]
# ) -> None:
#     dut.expect('Hello world!')
#     log_minimum_free_heap_size()
# 
# 
# def verify_elf_sha256_embedding(app: QemuApp, sha256_reported: str) -> None:
#     sha256 = hashlib.sha256()
#     with open(app.elf_file, 'rb') as f:
#         sha256.update(f.read())
#     sha256_expected = sha256.hexdigest()
# 
#     logging.info(f'ELF file SHA256: {sha256_expected}')
#     logging.info(f'ELF file SHA256 (reported by the app): {sha256_reported}')
# 
#     # the app reports only the first several hex characters of the SHA256, check that they match
#     if not sha256_expected.startswith(sha256_reported):
#         raise ValueError('ELF file SHA256 mismatch')
# 
# 
# @pytest.mark.esp32  # we only support qemu on esp32 for now
# @pytest.mark.host_test
# @pytest.mark.qemu
# def test_hello_world_host(app: QemuApp, dut: QemuDut) -> None:
#     sha256_reported = (
#         dut.expect(r'ELF file SHA256:\s+([a-f0-9]+)').group(1).decode('utf-8')
#     )
#     verify_elf_sha256_embedding(app, sha256_reported)
# 
#     dut.expect('Hello world!')
from __future__ import division, print_function, unicode_literals

import ttfw_idf


@ttfw_idf.idf_example_test(env_tag='Example_GENERIC', target=['esp32', 'esp32s2', 'esp32c3'], ci_target=['esp32'])
def test_examples_hello_world(env, extra_data):
    app_name = 'hello_world'
    dut = env.get_dut(app_name, 'examples/get-started/hello_world')
    dut.start_app()
    res = dut.expect(ttfw_idf.MINIMUM_FREE_HEAP_SIZE_RE)
    if not res:
        raise ValueError('Maximum heap size info not found')
    ttfw_idf.print_heap_size(app_name, dut.app.config_name, dut.TARGET, res[0])


if __name__ == '__main__':
    test_examples_hello_world()