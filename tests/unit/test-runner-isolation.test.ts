import { describe, expect, it } from 'vitest';
import { assertIsolatedProject } from '../test-runner-isolation.mjs';
import { evaluateAssertions } from '../test-runner-response-utils.mjs';
import { resolveCapturedValues } from '../test-runner.mjs';

const expected = {
  projectName: 'OwnedPCG', projectDir: 'D:/OwnedPCG/OwnedPCG.uproject',
  editorBaseDir: 'D:/UE/Engine/Binaries/Win64', engineVersionPrefix: '5.7.4-',
};
const identity = (projectDir = '../../../../OwnedPCG/') => ({ structuredContent: {
  success: true, data: { projectName: 'OwnedPCG', projectDir, engineVersion: '5.7.4-51494982' },
} });

describe('isolated integration project identity', () => {
  it('accepts matching relative editor paths and explicit local .uproject paths', () => {
    expect(() => assertIsolatedProject(identity(), expected)).not.toThrow();
    expect(() => assertIsolatedProject(identity('d:\\ownedpcg\\'), expected)).not.toThrow();
  });
  it('refuses another directory even when the project has the same name', () => {
    expect(() => assertIsolatedProject(identity('D:/Production/OwnedPCG/'), expected)).toThrow(/directory differs/);
  });
  it('fails closed without an explicit project selection or relative path base', () => {
    expect(() => assertIsolatedProject(identity(), {})).toThrow(/explicit projectName/);
    expect(() => assertIsolatedProject(identity(), { ...expected, editorBaseDir: undefined })).toThrow(/UE_EDITOR_BASE_DIR/);
  });
  it('refuses errors, redacted paths, and the wrong engine before mutation', () => {
    expect(() => assertIsolatedProject({ isError: true }, expected)).toThrow();
    expect(() => assertIsolatedProject(identity('[path redacted]'), expected)).toThrow();
    expect(() => assertIsolatedProject(identity(), { ...expected, engineVersionPrefix: '5.8.' })).toThrow(/engine version/);
  });
  it('does not apply Windows case folding to POSIX project paths', () => {
    const config = { projectName: 'OwnedPCG', projectDir: '/tmp/OwnedPCG' };
    expect(() => assertIsolatedProject(identity('/tmp/OwnedPCG'), config)).not.toThrow();
    expect(() => assertIsolatedProject(identity('/tmp/ownedpcg'), config)).toThrow(/directory differs/);
  });
  it('supports captured content revisions in post-failure assertions', () => {
    const assertions = resolveCapturedValues([{ path: 'structuredContent.result.revision', equals: '${captured:before}' }], { before: 'revision-1' });
    const response = { structuredContent: { data: { revision: 'revision-1' } } };
    expect(evaluateAssertions({ assertions }, response).passed).toBe(true);
    expect(evaluateAssertions({ assertions }, { structuredContent: { data: { revision: 'changed' } } }).passed).toBe(false);
  });
});
